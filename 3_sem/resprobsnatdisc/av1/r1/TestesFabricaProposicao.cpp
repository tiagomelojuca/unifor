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

  auto Imprime = [](IProposicao *p) {
    cout << (p ? (p->ValorLogico() ? "true" : "false") : "nullptr") << endl;
  };

  TFabricaProposicao fabrica;

  const std::string expr1 = "p ^ q v r";

  TInsumoFabricaProposicao expr1_e1(expr1);
  expr1_e1.DefineValorLogico("p", true);
  expr1_e1.DefineValorLogico("q", true);
  expr1_e1.DefineValorLogico("r", true);

  TInsumoFabricaProposicao expr1_e2(expr1);
  expr1_e2.DefineValorLogico("p", true);
  expr1_e2.DefineValorLogico("q", true);
  expr1_e2.DefineValorLogico("r", false);

  TInsumoFabricaProposicao expr1_e3(expr1);
  expr1_e3.DefineValorLogico("p", true);
  expr1_e3.DefineValorLogico("q", false);
  expr1_e3.DefineValorLogico("r", true);

  TInsumoFabricaProposicao expr1_e4(expr1);
  expr1_e4.DefineValorLogico("p", true);
  expr1_e4.DefineValorLogico("q", false);
  expr1_e4.DefineValorLogico("r", false);

  TInsumoFabricaProposicao expr1_e5(expr1);
  expr1_e5.DefineValorLogico("p", false);
  expr1_e5.DefineValorLogico("q", true);
  expr1_e5.DefineValorLogico("r", true);

  TInsumoFabricaProposicao expr1_e6(expr1);
  expr1_e6.DefineValorLogico("p", false);
  expr1_e6.DefineValorLogico("q", true);
  expr1_e6.DefineValorLogico("r", false);

  TInsumoFabricaProposicao expr1_e7(expr1);
  expr1_e7.DefineValorLogico("p", false);
  expr1_e7.DefineValorLogico("q", false);
  expr1_e7.DefineValorLogico("r", true);

  TInsumoFabricaProposicao expr1_e8(expr1);
  expr1_e8.DefineValorLogico("p", false);
  expr1_e8.DefineValorLogico("q", false);
  expr1_e8.DefineValorLogico("r", false);

  cout << "fabricando expr1::p1... ";
  IProposicao *expr1_p1 = fabrica.Fabrica(expr1_e1);
  cout << "fabricado!" << endl;

  cout << "fabricando expr1::p2... ";
  IProposicao *expr1_p2 = fabrica.Fabrica(expr1_e2);
  cout << "fabricado!" << endl;

  cout << "fabricando expr1::p3... ";
  IProposicao *expr1_p3 = fabrica.Fabrica(expr1_e3);
  cout << "fabricado!" << endl;

  cout << "fabricando expr1::p4... ";
  IProposicao *expr1_p4 = fabrica.Fabrica(expr1_e4);
  cout << "fabricado!" << endl;

  cout << "fabricando expr1::p5... ";
  IProposicao *expr1_p5 = fabrica.Fabrica(expr1_e5);
  cout << "fabricado!" << endl;

  cout << "fabricando expr1::p6... ";
  IProposicao *expr1_p6 = fabrica.Fabrica(expr1_e6);
  cout << "fabricado!" << endl;

  cout << "fabricando expr1::p7... ";
  IProposicao *expr1_p7 = fabrica.Fabrica(expr1_e7);
  cout << "fabricado!" << endl;

  cout << "fabricando expr1::p8... ";
  IProposicao *expr1_p8 = fabrica.Fabrica(expr1_e8);
  cout << "fabricado!" << endl;

  cout << endl;

  cout << expr1 << endl;
  Imprime(expr1_p1); // true
  Imprime(expr1_p2); // true
  Imprime(expr1_p3); // true
  Imprime(expr1_p4); // false
  Imprime(expr1_p5); // true
  Imprime(expr1_p6); // false
  Imprime(expr1_p7); // true
  Imprime(expr1_p8); // false
  cout << endl;

  delete expr1_p1;
  delete expr1_p2;
  delete expr1_p3;
  delete expr1_p4;
  delete expr1_p5;
  delete expr1_p6;
  delete expr1_p7;
  delete expr1_p8;

  const std::string expr2 = "(~a v b) ^ (b -> c) -> (a -> c)";

  TInsumoFabricaProposicao expr2_e1(expr2);
  expr2_e1.DefineValorLogico("a", true);
  expr2_e1.DefineValorLogico("b", true);
  expr2_e1.DefineValorLogico("c", true);

  TInsumoFabricaProposicao expr2_e2(expr2);
  expr2_e2.DefineValorLogico("a", true);
  expr2_e2.DefineValorLogico("b", true);
  expr2_e2.DefineValorLogico("c", false);

  TInsumoFabricaProposicao expr2_e3(expr2);
  expr2_e3.DefineValorLogico("a", true);
  expr2_e3.DefineValorLogico("b", false);
  expr2_e3.DefineValorLogico("c", true);

  TInsumoFabricaProposicao expr2_e4(expr2);
  expr2_e4.DefineValorLogico("a", true);
  expr2_e4.DefineValorLogico("b", false);
  expr2_e4.DefineValorLogico("c", false);

  TInsumoFabricaProposicao expr2_e5(expr2);
  expr2_e5.DefineValorLogico("a", false);
  expr2_e5.DefineValorLogico("b", true);
  expr2_e5.DefineValorLogico("c", true);

  TInsumoFabricaProposicao expr2_e6(expr2);
  expr2_e6.DefineValorLogico("a", false);
  expr2_e6.DefineValorLogico("b", true);
  expr2_e6.DefineValorLogico("c", false);

  TInsumoFabricaProposicao expr2_e7(expr2);
  expr2_e7.DefineValorLogico("a", false);
  expr2_e7.DefineValorLogico("b", false);
  expr2_e7.DefineValorLogico("c", true);

  TInsumoFabricaProposicao expr2_e8(expr2);
  expr2_e8.DefineValorLogico("a", false);
  expr2_e8.DefineValorLogico("b", false);
  expr2_e8.DefineValorLogico("c", false);

  cout << "fabricando expr2::p1... ";
  IProposicao *expr2_p1 = fabrica.Fabrica(expr2_e1);
  cout << "fabricado!" << endl;

  cout << "fabricando expr2::p2... ";
  IProposicao *expr2_p2 = fabrica.Fabrica(expr2_e2);
  cout << "fabricado!" << endl;

  cout << "fabricando expr2::p3... ";
  IProposicao *expr2_p3 = fabrica.Fabrica(expr2_e3);
  cout << "fabricado!" << endl;

  cout << "fabricando expr2::p4... ";
  IProposicao *expr2_p4 = fabrica.Fabrica(expr2_e4);
  cout << "fabricado!" << endl;

  cout << "fabricando expr2::p5... ";
  IProposicao *expr2_p5 = fabrica.Fabrica(expr2_e5);
  cout << "fabricado!" << endl;

  cout << "fabricando expr2::p6... ";
  IProposicao *expr2_p6 = fabrica.Fabrica(expr2_e6);
  cout << "fabricado!" << endl;

  cout << "fabricando expr2::p7... ";
  IProposicao *expr2_p7 = fabrica.Fabrica(expr2_e7);
  cout << "fabricado!" << endl;

  cout << "fabricando expr2::p8... ";
  IProposicao *expr2_p8 = fabrica.Fabrica(expr2_e8);
  cout << "fabricado!" << endl;

  cout << endl;

  cout << expr2 << endl;
  Imprime(expr2_p1); // true
  Imprime(expr2_p2); // true
  Imprime(expr2_p3); // true
  Imprime(expr2_p4); // true
  Imprime(expr2_p5); // true
  Imprime(expr2_p6); // true
  Imprime(expr2_p7); // true
  Imprime(expr2_p8); // true
  cout << endl;

  delete expr2_p1;
  delete expr2_p2;
  delete expr2_p3;
  delete expr2_p4;
  delete expr2_p5;
  delete expr2_p6;
  delete expr2_p7;
  delete expr2_p8;

  const std::string expr3 = "(p -> q) ^ ~p -> ~q";

  TInsumoFabricaProposicao expr3_e1(expr3);
  expr3_e1.DefineValorLogico("p", true);
  expr3_e1.DefineValorLogico("q", true);

  TInsumoFabricaProposicao expr3_e2(expr3);
  expr3_e2.DefineValorLogico("p", true);
  expr3_e2.DefineValorLogico("q", false);

  TInsumoFabricaProposicao expr3_e3(expr3);
  expr3_e3.DefineValorLogico("p", false);
  expr3_e3.DefineValorLogico("q", true);

  TInsumoFabricaProposicao expr3_e4(expr3);
  expr3_e4.DefineValorLogico("p", false);
  expr3_e4.DefineValorLogico("q", false);

  cout << "fabricando expr3::p1... ";
  IProposicao *expr3_p1 = fabrica.Fabrica(expr3_e1);
  cout << "fabricado!" << endl;

  cout << "fabricando expr3::p2... ";
  IProposicao *expr3_p2 = fabrica.Fabrica(expr3_e2);
  cout << "fabricado!" << endl;

  cout << "fabricando expr3::p3... ";
  IProposicao *expr3_p3 = fabrica.Fabrica(expr3_e3);
  cout << "fabricado!" << endl;

  cout << "fabricando expr3::p4... ";
  IProposicao *expr3_p4 = fabrica.Fabrica(expr3_e4);
  cout << "fabricado!" << endl;

  cout << endl;

  cout << expr3 << endl;
  Imprime(expr3_p1);
  Imprime(expr3_p2);
  Imprime(expr3_p3);
  Imprime(expr3_p4);
  cout << endl;

  delete expr3_p1;
  delete expr3_p2;
  delete expr3_p3;
  delete expr3_p4;

  const std::string expr4 = "p v ~(p ^ q)";

  TInsumoFabricaProposicao expr4_e1(expr4);
  expr4_e1.DefineValorLogico("p", true);
  expr4_e1.DefineValorLogico("q", true);

  TInsumoFabricaProposicao expr4_e2(expr4);
  expr4_e2.DefineValorLogico("p", true);
  expr4_e2.DefineValorLogico("q", false);

  TInsumoFabricaProposicao expr4_e3(expr4);
  expr4_e3.DefineValorLogico("p", false);
  expr4_e3.DefineValorLogico("q", true);

  TInsumoFabricaProposicao expr4_e4(expr4);
  expr4_e4.DefineValorLogico("p", false);
  expr4_e4.DefineValorLogico("q", false);

  cout << "fabricando expr4::p1... ";
  IProposicao *expr4_p1 = fabrica.Fabrica(expr4_e1);
  cout << "fabricado!" << endl;

  cout << "fabricando expr4::p2... ";
  IProposicao *expr4_p2 = fabrica.Fabrica(expr4_e2);
  cout << "fabricado!" << endl;

  cout << "fabricando expr4::p3... ";
  IProposicao *expr4_p3 = fabrica.Fabrica(expr4_e3);
  cout << "fabricado!" << endl;

  cout << "fabricando expr4::p4... ";
  IProposicao *expr4_p4 = fabrica.Fabrica(expr4_e4);
  cout << "fabricado!" << endl;

  cout << endl;

  cout << expr4 << endl;
  Imprime(expr4_p1); // true
  Imprime(expr4_p2); // true
  Imprime(expr4_p3); // true
  Imprime(expr4_p4); // true
  cout << endl;

  delete expr4_p1;
  delete expr4_p2;
  delete expr4_p3;
  delete expr4_p4;

  const std::string expr5 = "(p v q) ^ ~(p v q)";

  TInsumoFabricaProposicao expr5_e1(expr5);
  expr5_e1.DefineValorLogico("p", true);
  expr5_e1.DefineValorLogico("q", true);

  TInsumoFabricaProposicao expr5_e2(expr5);
  expr5_e2.DefineValorLogico("p", true);
  expr5_e2.DefineValorLogico("q", false);

  TInsumoFabricaProposicao expr5_e3(expr5);
  expr5_e3.DefineValorLogico("p", false);
  expr5_e3.DefineValorLogico("q", true);

  TInsumoFabricaProposicao expr5_e4(expr5);
  expr5_e4.DefineValorLogico("p", false);
  expr5_e4.DefineValorLogico("q", false);

  cout << "fabricando expr5::p1... ";
  IProposicao *expr5_p1 = fabrica.Fabrica(expr5_e1);
  cout << "fabricado!" << endl;

  cout << "fabricando expr5::p2... ";
  IProposicao *expr5_p2 = fabrica.Fabrica(expr5_e2);
  cout << "fabricado!" << endl;

  cout << "fabricando expr5::p3... ";
  IProposicao *expr5_p3 = fabrica.Fabrica(expr5_e3);
  cout << "fabricado!" << endl;

  cout << "fabricando expr5::p4... ";
  IProposicao *expr5_p4 = fabrica.Fabrica(expr5_e4);
  cout << "fabricado!" << endl;

  cout << endl;

  cout << expr5 << endl;
  Imprime(expr5_p1); // false
  Imprime(expr5_p2); // false
  Imprime(expr5_p3); // false
  Imprime(expr5_p4); // false
  cout << endl;

  delete expr5_p1;
  delete expr5_p2;
  delete expr5_p3;
  delete expr5_p4;

  cout << endl;
}
