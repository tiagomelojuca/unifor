#ifndef TABELAVERDADE_H_
#define TABELAVERDADE_H_

#include <string>
#include <vector>

#include "FabricaProposicoes.h"

class TTabelaVerdade {
public:
  TTabelaVerdade() = delete;
  TTabelaVerdade(const std::string &expr) : _expr(expr) {}
  ~TTabelaVerdade() { delete _vecInsumosProps; }

  bool Monta();
  std::string Stringify() const;

private:
  void AdicionaCabecalho();
  void AdicionaLinhas();
  void AdicionaLinha(const TInsumoProposicao &insumoProp);
  void AdicionaDivisoriaFinal();

  std::vector<std::string> IdentificadoresProposicoes();

  std::string Stringify(bool b) const;

  std::string _expr;
  std::vector<std::string> _lines;

  TFabricaProposicoes _fabrica;
  TVetorInsumosProposicoes *_vecInsumosProps = nullptr;
};

#endif // TABELAVERDADE_H_
