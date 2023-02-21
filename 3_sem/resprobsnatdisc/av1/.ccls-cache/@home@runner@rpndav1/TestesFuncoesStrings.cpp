#include "TestesFuncoesStrings.h"

#include <iostream>

#include "FuncoesStrings.h"

using namespace std;
namespace testes = TestesFuncoesStrings;

const std::string expr1 = "p ^ q";
const std::string expr2 = "p v q";
const std::string expr3 = "~p";
const std::string expr4 = "p ^ (q v ~(r v p))";
const std::string expr5 = "p ^ (q <-> ~(r <-> p))";
const std::string expr6 = "p ^ (q v ~(r <-> p))";
const std::string expr7 = "p <-> (q <-> ~(r <-> p))";

void testes::executa() {
  cout << "=== TestesFuncoesStrings ===" << endl;
  deve_ser_capaz_de_remover_whitespaces();
  deve_ser_capaz_de_separar_strings_por_primeiro_delimitador();
  deve_ser_capaz_de_separar_strings_por_ultimo_delimitador();
}

void testes::deve_ser_capaz_de_remover_whitespaces() {
  cout << "deve_ser_capaz_de_remover_whitespaces" << std::endl;

  cout << expr1 << " => " << FuncoesStrings::RemoverWhitespaces(expr1) << endl;
  cout << expr2 << " => " << FuncoesStrings::RemoverWhitespaces(expr2) << endl;
  cout << expr3 << " => " << FuncoesStrings::RemoverWhitespaces(expr3) << endl;
  cout << expr4 << " => " << FuncoesStrings::RemoverWhitespaces(expr4) << endl;

  cout << endl;
}

void testes::deve_ser_capaz_de_separar_strings_por_primeiro_delimitador() {
  cout << "deve_ser_capaz_de_separar_strings_por_primeiro_delimitador"
       << std::endl;

  using TParStrings = std::pair<std::string, std::string>;
  TParStrings a = FuncoesStrings::SeparaPrimeiro(expr5, "<->");
  cout << expr5 << " => \"" << a.first << "\" + \"" << a.second << "\"" << endl;

  TParStrings b = FuncoesStrings::SeparaPrimeiro(expr2, "<->");
  cout << expr2 << " => \"" << b.first << "\" + \"" << b.second << "\"" << endl;

  cout << endl;
}

void testes::deve_ser_capaz_de_separar_strings_por_ultimo_delimitador() {
  cout << "deve_ser_capaz_de_separar_strings_por_ultimo_delimitador"
       << std::endl;

  using TParStrings = std::pair<std::string, std::string>;
  TParStrings a = FuncoesStrings::SeparaUltimo(expr5, "<->");
  cout << expr5 << " => \"" << a.first << "\" + \"" << a.second << "\"" << endl;

  TParStrings b = FuncoesStrings::SeparaUltimo(expr2, "<->");
  cout << expr2 << " => \"" << b.first << "\" + \"" << b.second << "\"" << endl;

  TParStrings c = FuncoesStrings::SeparaUltimo(expr6, "<->");
  cout << expr6 << " => \"" << c.first << "\" + \"" << c.second << "\"" << endl;

  TParStrings d = FuncoesStrings::SeparaUltimo(expr7, "<->");
  cout << expr7 << " => \"" << d.first << "\" + \"" << d.second << "\"" << endl;

  cout << endl;
}
