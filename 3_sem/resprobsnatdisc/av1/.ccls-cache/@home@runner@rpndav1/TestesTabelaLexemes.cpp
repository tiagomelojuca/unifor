#include "TestesTabelaLexemes.h"

#include <iostream>

#include "TabelaLexemes.h"

using namespace std;
namespace testes = TestesTabelaLexemes;

void testes::executa() {
  cout << "=== TestesTabelaLexemes ===" << endl;
  deve_ser_capaz_de_obter_lexeme_a_partir_do_token();
  deve_ser_capaz_de_obter_token_a_partir_do_lexeme();
}

void testes::deve_ser_capaz_de_obter_lexeme_a_partir_do_token() {
  cout << "deve_ser_capaz_de_obter_lexeme_a_partir_do_token" << endl;

  TTabelaLexemes t;

  const string lex_b = "<lexeme>";  // lexeme_begin
  const string lex_e = "</lexeme>"; // lexeme_end

  cout << lex_b << t.Stringify("(") << lex_e << endl;
  cout << lex_b << t.Stringify(")") << lex_e << endl;
  cout << lex_b << t.Stringify("~") << lex_e << endl;
  cout << lex_b << t.Stringify("^") << lex_e << endl;
  cout << lex_b << t.Stringify("v") << lex_e << endl;
  cout << lex_b << t.Stringify("->") << lex_e << endl;
  cout << lex_b << t.Stringify("<->") << lex_e << endl;
  cout << lex_b << t.Stringify("bad_lex") << lex_e << endl;

  cout << endl;
}

void testes::deve_ser_capaz_de_obter_token_a_partir_do_lexeme() {
  cout << "deve_ser_capaz_de_obter_token_a_partir_do_lexeme" << std::endl;

  TTabelaLexemes t;

  const string tok_b = "<token>\"";  // token_begin
  const string tok_e = "\"</token>"; // token_end

  cout << tok_b << t.Lexeme(ELexemes::PRECEDENCIA_INICIO) << tok_e << endl;
  cout << tok_b << t.Lexeme(ELexemes::PRECEDENCIA_FIM) << tok_e << endl;
  cout << tok_b << t.Lexeme(ELexemes::NEGACAO) << tok_e << endl;
  cout << tok_b << t.Lexeme(ELexemes::CONJUNCAO) << tok_e << endl;
  cout << tok_b << t.Lexeme(ELexemes::DISJUNCAO) << tok_e << endl;
  cout << tok_b << t.Lexeme(ELexemes::CONDICIONAL) << tok_e << endl;
  cout << tok_b << t.Lexeme(ELexemes::BICONDICIONAL) << tok_e << endl;
  cout << tok_b << t.Lexeme(ELexemes::INVALIDO) << tok_e << endl;

  cout << endl;
}
