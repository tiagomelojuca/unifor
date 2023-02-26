#ifndef ANALISADORSINTATICO_H_
#define ANALISADORSINTATICO_H_

#include "Token.h"

class TAnalisadorSintatico {
public:
  TAnalisadorSintatico() = default;

  bool Verifica(const TTokenVector &tokens) const;

private:
  bool VerificaTokensValidos(const TTokenVector &tokens) const;
  bool VerificaOperacoes(const TTokenVector &tokens) const;
  bool VerificaPrecedencias(const TTokenVector &tokens) const;

  bool EhOperacao(const TToken &token) const;
  bool VerificaOperacao(const TToken &token) const;
  bool VerificaOperacaoUnaria(const TToken &token) const;
  bool VerificaOperacaoBinaria(const TToken &token) const;

  bool VerificaPrecedencias(const std::vector<TToken *> &tokens) const;
};

#endif // ANALISADORSINTATICO_H_
