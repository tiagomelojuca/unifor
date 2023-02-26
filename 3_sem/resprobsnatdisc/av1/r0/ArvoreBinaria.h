#include <algorithm>
#include <set>
#include <vector>

template <typename T> struct TNoArvoreBinaria {
  TNoArvoreBinaria(const T &data, TNoArvoreBinaria *pai = nullptr)
      : _data(new T(data)), _noPai(pai) {}

  ~TNoArvoreBinaria() {
    delete _data;
    delete _noEsq;
    delete _noDir;
  }

  void InsereFilhos(TNoArvoreBinaria *noEsq, TNoArvoreBinaria *noDir) {
    _noEsq = noEsq;
    _noDir = noDir;
  }

  bool TemFilhos() const { return _noEsq != nullptr || _noDir != nullptr; }

  T *_data = nullptr;
  TNoArvoreBinaria *_noEsq = nullptr;
  TNoArvoreBinaria *_noDir = nullptr;
  TNoArvoreBinaria *_noPai = nullptr;
};

template <typename T> class TArvoreBinaria {
public:
  TArvoreBinaria() = default;

  ~TArvoreBinaria() {
    delete _noEsq;
    delete _noDir;
  }

  void InsereFilhos(TNoArvoreBinaria<T> *noEsq, TNoArvoreBinaria<T> *noDir) {
    _noEsq = noEsq;
    _noDir = noDir;
  }

  bool Vazia() const { return _noEsq == nullptr && _noDir == nullptr; }

  // outras sugestoes de nome: NosFolhas | Folhas | LeafNodes
  std::vector<TNoArvoreBinaria<T> *> NosFolha() const {
    std::vector<TNoArvoreBinaria<T> *> folhas;

    if (!Vazia()) {
      PreencheComNosFilhos(folhas, _noEsq);
      PreencheComNosFilhos(folhas, _noDir);
    }

    return folhas;
  }

  std::vector<TNoArvoreBinaria<T> *> Caminho(TNoArvoreBinaria<T> *no) {
    std::vector<TNoArvoreBinaria<T> *> nos;

    nos.push_back(no);
    TNoArvoreBinaria<bool> *pai = no->_noPai;
    while (pai) {
      nos.push_back(pai);
      pai = pai->_noPai;
    }

    std::reverse(nos.begin(), nos.end());

    return nos;
  }

  std::vector<T> DadosOrdenadosRaizAoNo(TNoArvoreBinaria<T> *no) {
    std::vector<T> dadosOrdenados;

    std::vector<TNoArvoreBinaria<T> *> nos = Caminho(no);
    for (TNoArvoreBinaria<T> *no : nos) {
      dadosOrdenados.push_back(*no->_data);
    }

    return dadosOrdenados;
  }

private:
  void PreencheComNosFilhos(std::vector<TNoArvoreBinaria<T> *> &vec,
                            TNoArvoreBinaria<T> *no) const {
    if (!no->TemFilhos()) {
      vec.push_back(no);
    } else {
      PreencheComNosFilhos(vec, no->_noEsq);
      PreencheComNosFilhos(vec, no->_noDir);
    }
  }

  TNoArvoreBinaria<T> *_noEsq = nullptr;
  TNoArvoreBinaria<T> *_noDir = nullptr;
};
