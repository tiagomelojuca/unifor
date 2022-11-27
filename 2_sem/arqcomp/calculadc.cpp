// --------------------------------------------------------------------------------------
// DISCIPLINA DE ARQUITETURA DE COMPUTADORES
// BACHARELADO EM CIENCIA DA COMPUTACAO
// TRABALHO SOBRE DESEMPENHO EM CACHE
//
// DOCENTE:  VITOR ALENCAR DE MESQUITA
// DISCENTE: TIAGO MELO JUCA (2218781)
// --------------------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define  SENTINEL_VALUE std::numeric_limits<float>::min()

// --------------------------------------------------------------------------------------
// ESTRUTURAS AUXILIARES
// --------------------------------------------------------------------------------------

enum class ReplacementPolicies
{
    NONE,
    RANDOM,
    FIFO,
    LRU
};

// --------------------------------------------------------------------------------------

struct GraphInput
{
    GraphInput() = delete;
    GraphInput(uint16_t _cs, uint8_t _ad) : cacheSize(_cs), associativityDegree(_ad) {}

    bool operator==(const GraphInput& other) const
    {
        return cacheSize == other.cacheSize &&
               associativityDegree == other.associativityDegree;
    }

    uint16_t cacheSize;
    uint8_t  associativityDegree; // n-ways
};

// --------------------------------------------------------------------------------------

struct GraphOutput
{
    GraphOutput() = delete;
    GraphOutput(float _at, float _mr) : accessTime(_at), missRate(_mr) {}

    float accessTime;
    float missRate;
};

// --------------------------------------------------------------------------------------

struct GraphInputHasher
{
    std::size_t operator()(const GraphInput& gi) const
    {
        return gi.cacheSize + gi.associativityDegree;
    }
};

const std::unordered_map<GraphInput, GraphOutput, GraphInputHasher> graphData
{
    //GraphInput(CacheSize, N-Ways), GraphOutput(AccessTime, MissRate)
    { GraphInput(  16, 1), GraphOutput(0.571677632, 0.049707752) },
    { GraphInput(  16, 2), GraphOutput(0.731578947, 0.039000086) },
    { GraphInput(  32, 1), GraphOutput(0.606875000, 0.042927608) },
    { GraphInput(  32, 2), GraphOutput(0.767269737, 0.037585892) },
    { GraphInput(  64, 1), GraphOutput(0.679276316, 0.037617255) },
    { GraphInput(  64, 2), GraphOutput(0.863750000, 0.031351752) },
    { GraphInput( 128, 1), GraphOutput(0.774967105, 0.02208679) },
    { GraphInput( 128, 2), GraphOutput(1.023881579, 0.020038206) },
    { GraphInput( 256, 1), GraphOutput(0.880789474, 0.012271548) },
    { GraphInput( 256, 2), GraphOutput(1.253453947, 0.010941465) },
    { GraphInput( 512, 1), GraphOutput(1.041776316, 0.007160779) },
    { GraphInput( 512, 2), GraphOutput(1.673453947, 0.003864796) },
    { GraphInput(1024, 1), GraphOutput(1.339375000, 0.003823454) },
    { GraphInput(1024, 2), GraphOutput(2.147697368, 0.002614547) }
};

// --------------------------------------------------------------------------------------
// FUNCOES AUXILIARES
// --------------------------------------------------------------------------------------

std::string Stringify(ReplacementPolicies rp)
{
    if (rp == ReplacementPolicies::LRU)
    {
        return "LRU";
    }

    if (rp == ReplacementPolicies::FIFO)
    {
        return "FIFO";
    }

    if (rp == ReplacementPolicies::RANDOM)
    {
        return "RANDOM";
    }

    return "NONE";
}

// --------------------------------------------------------------------------------------

float ReplacementPolicyReducer(ReplacementPolicies rp)
{
    if (rp == ReplacementPolicies::LRU)
    {
        return 0.8;
    }

    if (rp == ReplacementPolicies::FIFO)
    {
        return 0.9;
    }

    return 1.0;
}

// --------------------------------------------------------------------------------------

bool IsValid(const GraphOutput& go)
{
    return go.accessTime != SENTINEL_VALUE && go.missRate != SENTINEL_VALUE;
}

// --------------------------------------------------------------------------------------

GraphOutput FindInGraph(const GraphInput& gi)
{
    auto it = graphData.find(gi);
    if (it != graphData.end())
    {
        return it->second;
    }

    return GraphOutput(SENTINEL_VALUE, SENTINEL_VALUE);
}

// --------------------------------------------------------------------------------------
// SISTEMA DE MEMORIA
// --------------------------------------------------------------------------------------

class MemorySystem
{
public:
    MemorySystem() = delete;
    MemorySystem(float mmt, uint16_t cs, uint8_t nw, ReplacementPolicies rp)
        : mainMemoryTime(mmt), cacheSize(cs), numWays(nw), replacementPolicy(rp),
          averageTime(SENTINEL_VALUE) {}
    uint16_t            CacheSize()         const { return cacheSize;         }
    uint8_t             NumWays()           const { return numWays;           }
    ReplacementPolicies ReplacementPolicy() const { return replacementPolicy; }

    double AverageTime();
    
    uint16_t Complexity() const;
    std::string Stringify() const;

private:
    double ComputeAverageTime() const;
    float ReplacementPolicyReducer(ReplacementPolicies rp) const;

    float mainMemoryTime;

    uint16_t cacheSize;
    uint8_t numWays;
    ReplacementPolicies replacementPolicy;

    double averageTime;
};

// --------------------------------------------------------------------------------------

double MemorySystem::AverageTime()
{
    if (averageTime != SENTINEL_VALUE)
    {
        return averageTime;
    }

    averageTime = ComputeAverageTime();
    return averageTime;
}

// --------------------------------------------------------------------------------------

uint16_t MemorySystem::Complexity() const
{
    if (numWays == 1)
    {
        return cacheSize;
    }

    int replacementPolicyComplexity;
    if (replacementPolicy == ReplacementPolicies::RANDOM)
    {
        replacementPolicyComplexity = 1;
    }
    else if (replacementPolicy == ReplacementPolicies::FIFO)
    {
        replacementPolicyComplexity = 2;
    }
    else if (replacementPolicy == ReplacementPolicies::LRU)
    {
        replacementPolicyComplexity = 3;
    }
    else
    {
        replacementPolicyComplexity = 0;
    }

    return cacheSize + replacementPolicyComplexity;
}

// --------------------------------------------------------------------------------------

std::string MemorySystem::Stringify() const
{
    std::stringstream _cacheSize;
    if (cacheSize < 1000) { _cacheSize << " "; }
    if (cacheSize < 100)  { _cacheSize << " "; }
    _cacheSize << cacheSize;

    std::stringstream _replacementPolicy;
    _replacementPolicy << ::Stringify(replacementPolicy);
    if (replacementPolicy == ReplacementPolicies::NONE) { _replacementPolicy <<  "  "; }
    if (replacementPolicy == ReplacementPolicies::FIFO) { _replacementPolicy <<  "  "; }
    if (replacementPolicy == ReplacementPolicies::LRU)  { _replacementPolicy << "   "; }

    std::stringstream ss;
    ss << "CACHE SIZE = "         << _cacheSize.str()          << " | "
       << "N-WAYS = "             << static_cast<int>(numWays) << " | "
       << "REPLACEMENT POLICY = " << _replacementPolicy.str()  << " | -> | "
       << "AVERAGE = "            << ComputeAverageTime();

    return ss.str();
}

// --------------------------------------------------------------------------------------

double MemorySystem::ComputeAverageTime() const
{
    const GraphOutput go = FindInGraph(GraphInput(cacheSize, numWays));
    if (!IsValid(go))
    {
        return SENTINEL_VALUE;
    }

    const float cacheTime = go.accessTime;
    const float missRate  = ReplacementPolicyReducer(replacementPolicy) * go.missRate;
    const float hitRate   = 1 - missRate;

    return mainMemoryTime * missRate + cacheTime * hitRate;
}

// --------------------------------------------------------------------------------------

float MemorySystem::ReplacementPolicyReducer(ReplacementPolicies rp) const
{
    return numWays > 1 ? ::ReplacementPolicyReducer(rp) : 1.0;
}

// --------------------------------------------------------------------------------------
// GERACAO DOS SISTEMAS DE MEMORIA
// --------------------------------------------------------------------------------------

std::vector<MemorySystem> ComputeStatistics(float mmTime)
{
    using RP = ReplacementPolicies;

    std::vector<MemorySystem> memSystems;
    for (int cacheSize = 16; cacheSize <= 1024; cacheSize *= 2)
    {
        memSystems.push_back(MemorySystem(mmTime, cacheSize, 1, RP::NONE));
        memSystems.push_back(MemorySystem(mmTime, cacheSize, 2, RP::RANDOM));
        memSystems.push_back(MemorySystem(mmTime, cacheSize, 2, RP::FIFO));
        memSystems.push_back(MemorySystem(mmTime, cacheSize, 2, RP::LRU));
    }

    return memSystems;
}

// --------------------------------------------------------------------------------------

void Filter(std::vector<MemorySystem>& v, std::function<bool(MemorySystem&)> pred)
{
    for (auto it = v.begin(); it != v.end();)
    {
        if (!pred(*it))
        {
            it = v.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// --------------------------------------------------------------------------------------

std::vector<MemorySystem> FindCandidates(float mmTime, float maxTime)
{
    std::vector<MemorySystem> memSystems = ComputeStatistics(mmTime);
    
    auto FilterCriteria = [maxTime](MemorySystem& ms)
    {
        return ms.AverageTime() <= maxTime;
    };
    Filter(memSystems, FilterCriteria);

    auto SortCriteria = [](const MemorySystem& ms1, const MemorySystem& ms2)
    {
        return ms1.Complexity() < ms2.Complexity();
    };
    std::sort(memSystems.begin(), memSystems.end(), SortCriteria);

    return memSystems;
}

// --------------------------------------------------------------------------------------
// IO
// --------------------------------------------------------------------------------------

void Trace(const std::vector<MemorySystem>& memSystems)
{
    for (const MemorySystem& memSystem : memSystems)
    {
        std::cout << memSystem.Stringify() << std::endl;
    }
}

// --------------------------------------------------------------------------------------

void Trace(float mainMemoryTime, float maxAverageTime)
{
    std::cout << "Computing statistics..." << std::endl;
    auto memSystems = ComputeStatistics(mainMemoryTime);
    for (const MemorySystem& memSystem : memSystems)
    {
        std::cout << memSystem.Stringify() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Finding candidates..." << std::endl;
    auto candidates = FindCandidates(mainMemoryTime, maxAverageTime);
    for (const MemorySystem& candidate : candidates)
    {
        std::cout << candidate.Stringify() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Finding winner..." << std::endl;
    std::cout << candidates[0].Stringify() << std::endl;
}

// --------------------------------------------------------------------------------------
// EXERCICIO
// --------------------------------------------------------------------------------------

std::unordered_map<uint16_t, std::string> labels
{
    {   16, "|   16 KB |" },
    {   32, "|   32 KB |" },
    {   64, "|   64 KB |" },
    {  128, "|  128 KB |" },
    {  256, "|  256 KB |" },
    {  512, "|  512 KB |" },
    { 1024, "| 1024 KB |" }
};

// --------------------------------------------------------------------------------------

void SolveExerciseA()
{
    std::cout << "A) Calculando o tempo de acesso a cache "
              << "para cada tamanho de memoria cache "
              << "usando mapeamento direto"
              << std::endl;

    const int nWays = 1;
    for (int cacheSize = 16; cacheSize <= 1024; cacheSize *= 2)
    {
        const GraphInput  gi(cacheSize, nWays);
        const GraphOutput go = FindInGraph(gi);

        std::cout << labels[cacheSize] << " " << go.accessTime << std::endl;
    }
}

// --------------------------------------------------------------------------------------

void SolveExerciseB()
{
    std::cout << "B) Calculando o tempo de acesso a cache "
              << "para cada tamanho de memoria cache "
              << "usando mapeamento associativo por conjuntos de 2 vias"
              << std::endl;

    const int nWays = 2;
    for (int cacheSize = 16; cacheSize <= 1024; cacheSize *= 2)
    {
        const GraphInput  gi(cacheSize, nWays);
        const GraphOutput go = FindInGraph(gi);

        std::cout << labels[cacheSize] << " " << go.accessTime << std::endl;
    }
}

// --------------------------------------------------------------------------------------

void SolveExerciseC()
{
    std::cout << "C) Calculando a taxa de cache miss "
              << "para cada tamanho de memoria cache "
              << "usando mapeamento direto"
              << std::endl;

    const int nWays = 1;
    for (int cacheSize = 16; cacheSize <= 1024; cacheSize *= 2)
    {
        const GraphInput  gi(cacheSize, nWays);
        const GraphOutput go = FindInGraph(gi);

        std::cout << labels[cacheSize] << " " << go.missRate << std::endl;
    }
}

// --------------------------------------------------------------------------------------

void SolveExerciseD()
{
    std::cout << "D) Calculando a taxa de cache miss "
              << "para cada tamanho de memoria cache "
              << "usando mapeamento associativo por conjuntos de 2 vias"
              << std::endl;

    const int nWays = 2;
    for (int cacheSize = 16; cacheSize <= 1024; cacheSize *= 2)
    {
        const GraphInput  gi(cacheSize, nWays);
        const GraphOutput go = FindInGraph(gi);

        std::cout << labels[cacheSize] << " " << go.missRate << std::endl;
    }
}

// --------------------------------------------------------------------------------------

void SolveExerciseE()
{
    std::cout << "E) Calculando a taxa de cache miss "
              << "para cada tamanho de memoria cache "
              << "usando mapeamento associativo por conjuntos de 2 vias "
              << "usando cada uma das politicas de substituicao RANDOM, FIFO e LRU"
              << std::endl;
    
    std::cout << "| CACHE   | "
              << "RANDOM       | "
              << "FIFO         | "
              << "LRU          |" << std::endl;
    const int nWays = 2;
    const float reducerFIFO = ReplacementPolicyReducer(ReplacementPolicies::FIFO);
    const float reducerLRU  = ReplacementPolicyReducer(ReplacementPolicies::LRU);

    for (int cacheSize = 16; cacheSize <= 1024; cacheSize *= 2)
    {
        const GraphInput  gi(cacheSize, nWays);
        const GraphOutput go = FindInGraph(gi);

        std::cout << labels[cacheSize]                          << " "
                  << std::setw(12) << go.missRate               << " | "
                  << std::setw(12) << go.missRate * reducerFIFO << " | "
                  << std::setw(12) << go.missRate * reducerLRU  << " | " << std::endl;
    }
}

// --------------------------------------------------------------------------------------

void SolveExerciseF(float mainMemoryTime)
{
    std::cout << "F) Calculando o tempo medio de acesso ao sistema de memoria "
              << "para cada tamanho de memoria cache "
              << "usando mapeamento direto"
              << std::endl;

    std::vector<MemorySystem> memSystems = ComputeStatistics(mainMemoryTime);
    Filter(memSystems, [](MemorySystem& ms) { return ms.NumWays() == 1U; });
    Trace(memSystems);
}

// --------------------------------------------------------------------------------------

void SolveExerciseG(float mainMemoryTime)
{
    std::cout << "G) Calculando o tempo medio de acesso ao sistema de memoria "
              << "para cada tamanho de memoria cache "
              << "usando mapeamento associativo por conjuntos de 2 vias "
              << "usando cada uma das politicas de substituicao RANDOM, FIFO e LRU"
              << std::endl;

    std::vector<MemorySystem> memSystems = ComputeStatistics(mainMemoryTime);
    Filter(memSystems, [](MemorySystem& ms) { return ms.NumWays() == 2U; });
    Trace(memSystems);
}

// --------------------------------------------------------------------------------------

void SolveExerciseH(float mainMemoryTime, float maxAverageTime)
{
    std::cout << "H) Escolhendo dentre as opcoes disponiveis a configuracao "
              << "mais simples de requisitos que mantenha "
              << "o tempo de acesso medio ao sistema de memoria "
              << "inferior a 2 nanosegundos"
              << std::endl;
    
    std::cout << FindCandidates(mainMemoryTime, maxAverageTime)[0].Stringify();
}

// --------------------------------------------------------------------------------------

void SolveExercise(float mainMemoryTime, float maxAverageTime)
{
    std::cout << "=== EXERCICIO ===" << std::endl;
    std::cout << std::endl; SolveExerciseA();
    std::cout << std::endl; SolveExerciseB();
    std::cout << std::endl; SolveExerciseC();
    std::cout << std::endl; SolveExerciseD();
    std::cout << std::endl; SolveExerciseE();
    std::cout << std::endl; SolveExerciseF(mainMemoryTime);
    std::cout << std::endl; SolveExerciseG(mainMemoryTime);
    std::cout << std::endl; SolveExerciseH(mainMemoryTime, maxAverageTime);
}

// --------------------------------------------------------------------------------------
// PONTO DE ENTRADA
// --------------------------------------------------------------------------------------

int main()
{
    const float mainMemoryTime = 30;
    const float maxAverageTime =  2;
    SolveExercise(mainMemoryTime, maxAverageTime);
}

// --------------------------------------------------------------------------------------
