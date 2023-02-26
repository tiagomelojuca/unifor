#include "TabelaVerdade.h"

bool TTabelaVerdade::Monta() {
  if (_vecInsumosProps == nullptr) {
    _vecInsumosProps = new TVetorInsumosProposicoes(_fabrica.Fabrica(_expr));

    if (!_vecInsumosProps->StdVector().empty()) {
      AdicionaCabecalho();
      AdicionaLinhas();
      AdicionaDivisoriaFinal();

      return true;
    }
  }

  return false;
}

std::string TTabelaVerdade::Stringify() const {
  std::string tabela = "";

  for (const std::string &_line : _lines) {
    tabela += _line;
    tabela += "\n";
  }

  return tabela;
}

void TTabelaVerdade::AdicionaCabecalho() {
  const std::vector<std::string> idsProps = IdentificadoresProposicoes();

  std::string cabecalho = "|   ";
  for (const std::string &idProp : idsProps) {
    cabecalho += idProp;
    cabecalho += "   |   ";
  }
  cabecalho += _expr;
  cabecalho += "   |";

  std::string divisoria = "";
  for (int i = 0; i < cabecalho.length(); i++) {
    divisoria += "-";
  }

  _lines.push_back(divisoria);
  _lines.push_back(cabecalho);
  _lines.push_back(divisoria);
}

void TTabelaVerdade::AdicionaLinhas() {
  std::vector<TInsumoProposicao *> &paresInsumosProps =
      _vecInsumosProps->StdVector();

  for (TInsumoProposicao *parInsumoProp : paresInsumosProps) {
    AdicionaLinha(*parInsumoProp);
  }
}

void TTabelaVerdade::AdicionaLinha(const TInsumoProposicao &insumoProp) {
  const TInsumoFabricaProposicao &insumo = insumoProp.Insumo();
  const IProposicao &prop = insumoProp.Proposicao();

  const std::vector<std::string> idsProps = IdentificadoresProposicoes();

  std::string _line = "|   ";
  for (const std::string &idProp : idsProps) {
    _line += Stringify(insumo.ValorLogico(idProp));
    _line += "   |   ";
  }
  _line += Stringify(prop.ValorLogico());
  _line += "   |";

  _lines.push_back(_line);
}

void TTabelaVerdade::AdicionaDivisoriaFinal() {
  const size_t larguraTabela = _lines.back().length();

  std::string divisoria = "";
  for (int i = 0; i < larguraTabela; i++) {
    divisoria += "-";
  }

  _lines.push_back(divisoria);
}

std::vector<std::string> TTabelaVerdade::IdentificadoresProposicoes() {
  std::vector<TInsumoProposicao *> &stdVec = _vecInsumosProps->StdVector();
  const TInsumoFabricaProposicao &insumo = stdVec.front()->Insumo();
  // outras sugestoes nome: qualquerInsumo | insumoReferencia | insumoRef

  return insumo.IdentificadoresProposicoes();
}

std::string TTabelaVerdade::Stringify(bool b) const { return b ? "V" : "F"; }
