#include "Token.h"

TToken::TToken(const std::string &token, ETipoToken tipoToken)
    : _token(token), _tipoToken(tipoToken), _corrente(this) {
  // nothing
}

const std::string &TToken::Token() const {
  // acesso ao token como string
  return _token;
}

ETipoToken TToken::TipoToken() const {
  // acesso ao tipo do token
  return _tipoToken;
}

TToken *TToken::TokenAnterior() const {
  // obtem token antecedente
  return _anterior;
}

TToken *TToken::TokenCorrente() const {
  // obtem o proprio token; despreza constness (const_cast)
  return _corrente;
}

TToken *TToken::TokenSeguinte() const {
  // obtem token subsequente
  return _seguinte;
}

void TToken::TokenAnterior(TToken *anterior) {
  // reatribui token antecedente
  _anterior = anterior;
}

void TToken::TokenSeguinte(TToken *seguinte) {
  // reatribui token subsequente
  _seguinte = seguinte;
}

TTokenVector::~TTokenVector() {
  for (TToken *token : _tokens) {
    delete token;
  }
}

void TTokenVector::PushToken(const TToken &token) {
  TToken *_token = new TToken(token.Token(), token.TipoToken());

  if (!_tokens.empty()) {
    _token->TokenAnterior(_tokens.back());
    _tokens.back()->TokenSeguinte(_token);
  }

  _tokens.push_back(_token);
}

TToken *TTokenVector::Begin() const {
  // first element of vector
  return _tokens.front();
}

TToken *TTokenVector::End() const {
  // last element of vector
  return _tokens.back();
}

const std::vector<TToken *> &TTokenVector::RawVector() const {
  // obtem raw vector de tokens
  return _tokens;
}

size_t
TTokenVector::BuscaPrimeiraOcorrencia(const std::vector<TToken *> &tokens,
                                      ETipoToken tipo) {
  for (size_t i = 0; i < tokens.size(); i++) {
    const TToken &token = *tokens[i];
    if (token.TipoToken() == tipo) {
      return i;
    }
  }

  return SIZE_MAX;
}

size_t TTokenVector::BuscaUltimaOcorrencia(const std::vector<TToken *> &tokens,
                                           ETipoToken tipo) {
  if (!tokens.empty()) {
    size_t i = tokens.size() - 1;
    while (true) {
      const TToken &token = *tokens[i];
      if (token.TipoToken() == tipo) {
        return i;
      }

      if (i == 0) {
        break;
      }

      i--;
    }
  }

  return SIZE_MAX;
}

size_t
TTokenVector::BuscaPrimeiraOcorrencia(const std::vector<TToken *> &tokens,
                                      ELexemes lexeme) {
  TTabelaLexemes tabelaLexemes;

  for (size_t i = 0; i < tokens.size(); i++) {
    const TToken &token = *tokens[i];
    if (token.Token() == tabelaLexemes.Lexeme(lexeme)) {
      return i;
    }
  }

  return SIZE_MAX;
}

size_t TTokenVector::BuscaUltimaOcorrencia(const std::vector<TToken *> &tokens,
                                           ELexemes lexeme) {
  TTabelaLexemes tabelaLexemes;

  if (!tokens.empty()) {
    size_t i = tokens.size() - 1;
    while (true) {
      const TToken &token = *tokens[i];
      if (token.Token() == tabelaLexemes.Lexeme(lexeme)) {
        return i;
      }

      if (i == 0) {
        break;
      }

      i--;
    }
  }

  return SIZE_MAX;
}
