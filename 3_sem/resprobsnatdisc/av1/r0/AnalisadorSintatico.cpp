#include "AnalisadorSintatico.h"

bool TAnalisadorSintatico::Verifica(const TTokenVector &tokens) const {
  if (!VerificaTokensValidos(tokens)) {
    return false;
  }

  if (!VerificaOperacoes(tokens)) {
    return false;
  }

  if (!VerificaPrecedencias(tokens)) {
    return false;
  }

  return true;
}

bool TAnalisadorSintatico::VerificaTokensValidos(
    const TTokenVector &tokens) const {

  TToken *it = tokens.Begin();
  while (it) {
    TToken *tokenCorrente = it;
    it = it->TokenSeguinte();

    if (tokenCorrente->TipoToken() == ETipoToken::INVALIDO) {
      return false;
    }
  }

  return true;
}

bool TAnalisadorSintatico::VerificaOperacoes(const TTokenVector &tokens) const {
  for (const TToken *token : tokens.RawVector()) {
    if (EhOperacao(*token) && !VerificaOperacao(*token)) {
      return false;
    }
  }

  return true;
}

bool TAnalisadorSintatico::VerificaPrecedencias(
    const TTokenVector &tokens) const {
  // efetua copia do raw vector, nao altera ownership (que eh de TTokenVector)
  std::vector<TToken *> rawVec = tokens.RawVector();
  return VerificaPrecedencias(rawVec);
}

bool TAnalisadorSintatico::EhOperacao(const TToken &token) const {
  const ETipoToken tipoToken = token.TipoToken();

  return tipoToken == ETipoToken::OPERACAO_UNARIA ||
         tipoToken == ETipoToken::OPERACAO_BINARIA;
}

bool TAnalisadorSintatico::VerificaOperacao(const TToken &token) const {
  if (token.TokenSeguinte() == nullptr) {
    return false;
  }

  if (token.TipoToken() == ETipoToken::OPERACAO_UNARIA) {
    return VerificaOperacaoUnaria(token);
  }

  if (token.TipoToken() == ETipoToken::OPERACAO_BINARIA) {
    return VerificaOperacaoBinaria(token);
  }

  return true;
}

bool TAnalisadorSintatico::VerificaOperacaoUnaria(const TToken &token) const {
  const ETipoToken tipoTokenSeguinte = token.TokenSeguinte()->TipoToken();

  if (tipoTokenSeguinte != ETipoToken::PROPOSICAO &&
      tipoTokenSeguinte != ETipoToken::OPERACAO_UNARIA &&
      tipoTokenSeguinte != ETipoToken::ESPECIFICADOR_PRECEDENCIA_I) {
    return false;
  }

  return true;
}

bool TAnalisadorSintatico::VerificaOperacaoBinaria(const TToken &token) const {
  const TToken *tokenAnterior = token.TokenAnterior();
  const TToken *tokenSeguinte = token.TokenSeguinte();

  if (tokenAnterior == nullptr || tokenSeguinte == nullptr) {
    return false;
  }

  const ETipoToken tipoTokenAnterior = tokenAnterior->TipoToken();

  if (tipoTokenAnterior != ETipoToken::PROPOSICAO &&
      tipoTokenAnterior != ETipoToken::ESPECIFICADOR_PRECEDENCIA_F) {
    return false;
  }

  const ETipoToken tipoTokenSeguinte = tokenSeguinte->TipoToken();

  if (tipoTokenSeguinte != ETipoToken::PROPOSICAO &&
      tipoTokenSeguinte != ETipoToken::OPERACAO_UNARIA &&
      tipoTokenSeguinte != ETipoToken::ESPECIFICADOR_PRECEDENCIA_I) {
    return false;
  }

  return true;
}

bool TAnalisadorSintatico::VerificaPrecedencias(
    const std::vector<TToken *> &tokens) const {
  const size_t posI = TTokenVector::BuscaPrimeiraOcorrencia(
      tokens, ETipoToken::ESPECIFICADOR_PRECEDENCIA_I);

  const size_t posF = TTokenVector::BuscaUltimaOcorrencia(
      tokens, ETipoToken::ESPECIFICADOR_PRECEDENCIA_F);

  if (posI != SIZE_MAX && posF == SIZE_MAX) {
    return false;
  }

  if (posI == SIZE_MAX && posF != SIZE_MAX) {
    return false;
  }

  if (posF == posI + 1) {
    return false;
  }

  if (posI == SIZE_MAX && posF == SIZE_MAX) {
    return true;
  }

  std::vector<TToken *> tokensEntrePrecedencia;
  for (size_t i = posI + 1; i < posF; i++) {
    tokensEntrePrecedencia.push_back(tokens[i]);
  }

  return VerificaPrecedencias(tokensEntrePrecedencia);
}
