#ifndef ANALISADORLEXICO_H_
#define ANALISADORLEXICO_H_

#include <string>
#include <vector>

#include "TabelaLexemes.h"
#include "Token.h"

class TAnalisadorLexico {
public:
  TAnalisadorLexico() = default;

  std::vector<std::string> ParseTokens(const std::string &cadeia) const;
  TTokenVector GeraListaTokens(const std::string &cadeia) const;

private:
  std::vector<std::string> QuebraCadeia(const std::vector<std::string> &cadeias,
                                        ELexemes lexeme) const;

  std::vector<std::string> QuebraCadeia(const std::string &cadeia,
                                        ELexemes lexeme) const;

  ETipoToken IdentificaTipo(const std::string &token) const;

  TTabelaLexemes _tabelaLexemes;
};

#endif // ANALISADORLEXICO_H_
