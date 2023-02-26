#ifndef FABRICAPROPOSICOES_H_
#define FABRICAPROPOSICOES_H_

#include <string>
#include <vector>

#include "ArvoreBinaria.h"
#include "FabricaProposicao.h"
#include "Proposicao.h"

// outras sugestoes de nomes
// TAssociacaoInsumoProposicao | TParInsumoProposicao
class TInsumoProposicao {
public:
  TInsumoProposicao() = delete;
  TInsumoProposicao(TInsumoFabricaProposicao *insumo, IProposicao *prop)
      : _insumo(insumo), _proposicao(prop) {}

  ~TInsumoProposicao() {
    delete _insumo;
    delete _proposicao;
  }

  const TInsumoFabricaProposicao &Insumo() const { return *_insumo; }
  const IProposicao &Proposicao() const { return *_proposicao; }

private:
  TInsumoFabricaProposicao *_insumo = nullptr;
  IProposicao *_proposicao = nullptr;
};

// Casca para std::vector usando RAII
class TVetorInsumosProposicoes {
public:
  TVetorInsumosProposicoes() = default;
  ~TVetorInsumosProposicoes() {
    for (TInsumoProposicao *_insumoProp : _insumosProps) {
      delete _insumoProp;
    }
  }
  std::vector<TInsumoProposicao *> &StdVector() { return _insumosProps; }

private:
  std::vector<TInsumoProposicao *> _insumosProps;
};

class TFabricaProposicoes {
public:
  TFabricaProposicoes() = default;

  TVetorInsumosProposicoes Fabrica(const std::string &expr) const;

private:
  std::vector<TInsumoFabricaProposicao>
  GeraInsumos(const std::string &expr) const;

  TArvoreBinaria<bool> GeraCombinacoesTabelaVerdade(size_t entradas) const;

  std::vector<std::string>
  IdentificadoresProposicoes(const std::string &expr) const;

  TFabricaProposicao _fabricaProposicao;
};

#endif // FABRICAPROPOSICOES_H_
