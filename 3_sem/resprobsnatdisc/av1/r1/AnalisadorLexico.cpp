#include "AnalisadorLexico.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "FuncoesStrings.h"
#include "TabelaLexemes.h"

namespace FS = FuncoesStrings;

std::vector<std::string>
TAnalisadorLexico::ParseTokens(const std::string &cadeia) const {
  std::vector<std::string> tokens;

  tokens.push_back(FS::RemoverWhitespaces(cadeia));
  tokens = QuebraCadeia(tokens, ELexemes::PRECEDENCIA_INICIO);
  tokens = QuebraCadeia(tokens, ELexemes::PRECEDENCIA_FIM);
  tokens = QuebraCadeia(tokens, ELexemes::BICONDICIONAL);
  tokens = QuebraCadeia(tokens, ELexemes::CONDICIONAL);
  tokens = QuebraCadeia(tokens, ELexemes::NEGACAO);
  tokens = QuebraCadeia(tokens, ELexemes::CONJUNCAO);
  tokens = QuebraCadeia(tokens, ELexemes::DISJUNCAO);

  return tokens;
}

TTokenVector
TAnalisadorLexico::GeraListaTokens(const std::string &cadeia) const {
  TTokenVector tokens;

  for (const std::string &token : ParseTokens(cadeia)) {
    tokens.PushToken(TToken(token, IdentificaTipo(token)));
  }

  return tokens;
}

std::vector<std::string>
TAnalisadorLexico::QuebraCadeia(const std::vector<std::string> &cadeias,
                                ELexemes lexeme) const {
  std::vector<std::string> subcadeias;

  for (const std::string &cadeia : cadeias) {
    for (const std::string &subcadeia : QuebraCadeia(cadeia, lexeme)) {
      subcadeias.push_back(subcadeia);
    }
  }

  return subcadeias;
}

std::vector<std::string>
TAnalisadorLexico::QuebraCadeia(const std::string &cadeia,
                                ELexemes lexeme) const {
  std::vector<std::string> subcadeias;

  const bool cadeiaEhQualquerLexeme =
      _tabelaLexemes.Lexeme(cadeia) != ELexemes::INVALIDO;
  if (cadeiaEhQualquerLexeme) {
    subcadeias.push_back(cadeia);
    return subcadeias;
  }

  const std::string lexemeStr = _tabelaLexemes.Lexeme(lexeme);

  std::string str = cadeia;
  while (str.find(lexemeStr) != std::string::npos) {
    auto par = FS::SeparaPrimeiro(str, lexemeStr);
    subcadeias.push_back(par.first);
    subcadeias.push_back(lexemeStr);
    str = par.second;
  }
  subcadeias.push_back(str);

  for (auto it = subcadeias.begin(); it != subcadeias.end();) {
    if (*it == "") {
      it = subcadeias.erase(it);
    } else {
      ++it;
    }
  }

  return subcadeias;
}

ETipoToken TAnalisadorLexico::IdentificaTipo(const std::string &token) const {
  auto lexeme = _tabelaLexemes.Lexeme(token);

  if (lexeme == ELexemes::PRECEDENCIA_INICIO) {
    return ETipoToken::ESPECIFICADOR_PRECEDENCIA_I;
  }

  if (lexeme == ELexemes::PRECEDENCIA_FIM) {
    return ETipoToken::ESPECIFICADOR_PRECEDENCIA_F;
  }

  if (lexeme == ELexemes::NEGACAO) {
    return ETipoToken::OPERACAO_UNARIA;
  }

  if (lexeme == ELexemes::CONJUNCAO || lexeme == ELexemes::DISJUNCAO ||
      lexeme == ELexemes::CONDICIONAL || lexeme == ELexemes::BICONDICIONAL) {
    return ETipoToken::OPERACAO_BINARIA;
  }

  if (token.length() > 1) {
    return ETipoToken::INVALIDO;
  }

  return ETipoToken::PROPOSICAO;
}