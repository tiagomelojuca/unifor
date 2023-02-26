#include "TestesFabricaProposicao.h"

#include <iostream>

#include "FabricaProposicao.h"

using namespace std;
namespace testes = TestesFabricaProposicao;

void testes::executa() {
  cout << "=== TestesFabricaProposicao ===" << endl;
  deve_ser_capaz_de_gerar_linhas_da_tv_tabela_verdade();
}

void testes::deve_ser_capaz_de_gerar_linhas_da_tv_tabela_verdade() {
  cout << "deve_ser_capaz_de_gerar_linhas_da_tv_tabela_verdade" << endl;

  TFabricaProposicao fabrica;

  const std::string expressao = "p ^ q v r";

  TInsumoFabricaProposicao e1(expressao);
  e1.DefineValorLogico("p", true);
  e1.DefineValorLogico("q", true);
  e1.DefineValorLogico("r", true);

  TInsumoFabricaProposicao e2(expressao);
  e2.DefineValorLogico("p", true);
  e2.DefineValorLogico("q", true);
  e2.DefineValorLogico("r", false);

  TInsumoFabricaProposicao e3(expressao);
  e3.DefineValorLogico("p", true);
  e3.DefineValorLogico("q", false);
  e3.DefineValorLogico("r", true);

  TInsumoFabricaProposicao e4(expressao);
  e4.DefineValorLogico("p", true);
  e4.DefineValorLogico("q", false);
  e4.DefineValorLogico("r", false);

  TInsumoFabricaProposicao e5(expressao);
  e5.DefineValorLogico("p", false);
  e5.DefineValorLogico("q", true);
  e5.DefineValorLogico("r", true);

  TInsumoFabricaProposicao e6(expressao);
  e6.DefineValorLogico("p", false);
  e6.DefineValorLogico("q", true);
  e6.DefineValorLogico("r", false);

  TInsumoFabricaProposicao e7(expressao);
  e7.DefineValorLogico("p", false);
  e7.DefineValorLogico("q", false);
  e7.DefineValorLogico("r", true);

  TInsumoFabricaProposicao e8(expressao);
  e8.DefineValorLogico("p", false);
  e8.DefineValorLogico("q", false);
  e8.DefineValorLogico("r", false);

  IProposicao *p1 = fabrica.Fabrica(e1); // true
  IProposicao *p2 = fabrica.Fabrica(e2); // true
  IProposicao *p3 = fabrica.Fabrica(e3); // true
  IProposicao *p4 = fabrica.Fabrica(e4); // false
  IProposicao *p5 = fabrica.Fabrica(e5); // true
  IProposicao *p6 = fabrica.Fabrica(e6); // false
  IProposicao *p7 = fabrica.Fabrica(e7); // true
  IProposicao *p8 = fabrica.Fabrica(e8); // false

  cout << expressao << endl;
  cout << (p1 ? (p1->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  cout << (p2 ? (p2->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  cout << (p3 ? (p3->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  cout << (p4 ? (p4->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  cout << (p5 ? (p5->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  cout << (p6 ? (p6->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  cout << (p7 ? (p7->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  cout << (p8 ? (p8->ValorLogico() ? "true" : "false") : "nullptr") << endl;

  delete p1;
  delete p2;
  delete p3;
  delete p4;
  delete p5;
  delete p6;
  delete p7;
  delete p8;

  cout << endl;
}