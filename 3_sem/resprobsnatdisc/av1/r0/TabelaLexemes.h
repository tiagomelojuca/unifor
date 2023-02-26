#ifndef TABELALEXEMES_H_
#define TABELALEXEMES_H_

#include <map>
#include <string>

enum class ELexemes {
  INVALIDO,
  PRECEDENCIA_INICIO,
  PRECEDENCIA_FIM,
  NEGACAO,
  CONJUNCAO,
  DISJUNCAO,
  CONDICIONAL,
  BICONDICIONAL
};

class TTabelaLexemes {
public:
  TTabelaLexemes();

  ELexemes Lexeme(const std::string &lexeme) const;
  std::string Lexeme(ELexemes lexeme) const;

  std::string Stringify(ELexemes lexeme) const;
  std::string Stringify(const std::string &lexeme) const;

private:
  std::map<std::string, ELexemes> _tabela;
};

#endif // TABELALEXEMES_H_
