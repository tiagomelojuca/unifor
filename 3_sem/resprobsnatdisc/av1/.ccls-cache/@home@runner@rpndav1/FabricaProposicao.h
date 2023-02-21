#ifndef FABRICAPROPOSICAO_H_
#define FABRICAPROPOSICAO_H_

#include <map>
#include <string>

#include "AnalisadorLexico.h"
#include "AnalisadorSintatico.h"
#include "Proposicao.h"
#include "TabelaLexemes.h"

// outras sugestoes de nome
// TMateriaPrimaFabricaProposicao | TInputPropositionFactory
class TInsumoFabricaProposicao {
public:
  TInsumoFabricaProposicao() = delete;
  TInsumoFabricaProposicao(const std::string &expr);

  const std::string &Expressao() const;

  void DefineValorLogico(const std::string &identificador, bool valorLogico);
  bool PossuiValorLogico(const std::string &identificador) const;
  bool ValorLogico(const std::string &identificador) const;

  std::vector<std::string> IdentificadoresProposicoes() const;

private:
  std::string _expressao;
  std::map<std::string, bool> _valoresLogicos;
};

class TFabricaProposicao {
public:
  TFabricaProposicao() = default;

  IProposicao *Fabrica(const TInsumoFabricaProposicao &entrada) const;

private:
  IProposicao *Fabrica(const TInsumoFabricaProposicao &entrada,
                       const std::vector<TToken *> &tokens) const;

  IProposicao *
  FabricaProposicaoSimples(const TInsumoFabricaProposicao &entrada,
                           const std::vector<TToken *> &tokens) const;

  IProposicao *
  FabricaProposicaoComposta(const TInsumoFabricaProposicao &entrada,
                            const std::vector<TToken *> &tokens,
                            ELexemes lexeme) const;

  IProposicao *
  FabricaProposicaoFilha(const TInsumoFabricaProposicao &entrada,
                         const std::vector<TToken *> &tokens) const;
  // outras sugestoes de nome, decidir depois
  // FabricaSubExpressao | FabricaSubExpr | FabricaSubProposicao
  // ChildPropositionFactory | SubExpressionFactory | SubExprFactory

  TInsumoFabricaProposicao
  FabricaInsumoFilho(const std::string &subexpr,
                     const TInsumoFabricaProposicao &parent) const;
  // outras sugestoes de nome, decidir depois
  // FabricaSubInsumo | trocar parent por insumoPai
  // ChildInputFactory | SubInputFactory

  bool DeveAplicarNegacao(const TToken &token) const;

  std::vector<TToken *> FiltraIdentificadores(const TTokenVector &tokens) const;

  TTabelaLexemes _tabelaLexemes;
  TAnalisadorLexico _analisadorLexico;
  TAnalisadorSintatico _analisadorSintatico;
};

#endif // FABRICAPROPOSICAO_H_
