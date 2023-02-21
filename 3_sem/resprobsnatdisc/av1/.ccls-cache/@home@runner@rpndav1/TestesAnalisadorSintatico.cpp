#include "TestesAnalisadorSintatico.h"

#include <iostream>

#include "AnalisadorSintatico.h"

#include "AnalisadorLexico.h"

using namespace std;
namespace testes = TestesAnalisadorSintatico;

void testes::executa() {
  cout << "=== TestesAnalisadorSintatico ===" << endl;
  deve_ser_capaz_de_verificar_se_atende_aos_requisitos_de_uma_fbf_formula_bem_formulada();
}

void testes::
    deve_ser_capaz_de_verificar_se_atende_aos_requisitos_de_uma_fbf_formula_bem_formulada() {
  cout << "deve_ser_capaz_de_verificar_se_atende_aos_requisitos_de_uma_fbf_"
       << "formula_bem_formulada" << endl;

  TAnalisadorSintatico analisador;

  TAnalisadorLexico anlex;
  auto _PrintStatus = [&analisador, &anlex](const std::string &expr) {
    const bool b = analisador.Verifica(anlex.GeraListaTokens(expr));
    cout << expr << " [[ isValid = " << (b ? "true" : "false") << " ]]" << endl;
  };

  cout << "[expect TRUE]" << endl;
  _PrintStatus("~~~p");
  _PrintStatus("p ^ q v ~(r v p)");
  _PrintStatus("p ^ q v (r v p)");
  _PrintStatus("p ^ q v (~r v p)");
  _PrintStatus("p ^ q v r");
  _PrintStatus("p ^~ q v r");
  _PrintStatus("(a) -> b");
  _PrintStatus("(a -> b) ^ (b -> a)");

  cout << endl << "[expect FALSE]" << endl;
  _PrintStatus("pz ^ q v ~(r v p)");
  _PrintStatus("z ^ qf v ~(r v p)");
  _PrintStatus("p ^^ q v ~(r v p)");
  _PrintStatus("p ^ q vv ~(r v p)");
  _PrintStatus("p ^ q v (~r v p~)");
  _PrintStatus("p ^ q v (~r v p)~");
  _PrintStatus("p ^ q v (~r v p)v");
  _PrintStatus("p ^ q v <-> (~r v p)");
  _PrintStatus("v p ^ q v (~r v p)");
  _PrintStatus("p ~^ q v r");
  _PrintStatus("a) -> b");
  _PrintStatus("a) ^ -> b");
  _PrintStatus("a)) ^^ -> bc");

  cout << endl;
}