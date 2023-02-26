#include "TabelaLexemes.h"

TTabelaLexemes::TTabelaLexemes() {
  _tabela["("] = ELexemes::PRECEDENCIA_INICIO;
  _tabela[")"] = ELexemes::PRECEDENCIA_FIM;
  _tabela["~"] = ELexemes::NEGACAO;
  _tabela["^"] = ELexemes::CONJUNCAO;
  _tabela["v"] = ELexemes::DISJUNCAO;
  _tabela["->"] = ELexemes::CONDICIONAL;
  _tabela["<->"] = ELexemes::BICONDICIONAL;
}

ELexemes TTabelaLexemes::Lexeme(const std::string &lexeme) const {
  auto it = _tabela.find(lexeme);
  if (it != _tabela.end()) {
    return it->second;
  }

  return ELexemes::INVALIDO;
}

std::string TTabelaLexemes::Lexeme(ELexemes lexeme) const {
  for (auto it = _tabela.begin(); it != _tabela.end(); ++it) {
    if (it->second == lexeme) {
      return it->first;
    }
  }

  return "";
}

std::string TTabelaLexemes::Stringify(ELexemes lexeme) const {
  if (lexeme == ELexemes::PRECEDENCIA_INICIO) {
    return "PRECEDENCIA_INICIO";
  }

  if (lexeme == ELexemes::PRECEDENCIA_FIM) {
    return "PRECEDENCIA_FIM";
  }

  if (lexeme == ELexemes::NEGACAO) {
    return "NEGACAO";
  }

  if (lexeme == ELexemes::CONJUNCAO) {
    return "CONJUNCAO";
  }

  if (lexeme == ELexemes::DISJUNCAO) {
    return "DISJUNCAO";
  }

  if (lexeme == ELexemes::CONDICIONAL) {
    return "CONDICIONAL";
  }

  if (lexeme == ELexemes::BICONDICIONAL) {
    return "BICONDICIONAL";
  }

  return "INVALIDO";
}

std::string TTabelaLexemes::Stringify(const std::string &lexeme) const {
  return Stringify(Lexeme(lexeme));
}
