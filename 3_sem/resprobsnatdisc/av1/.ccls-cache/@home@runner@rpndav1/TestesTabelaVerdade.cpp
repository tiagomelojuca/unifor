#include "TestesTabelaVerdade.h"

#include <iostream>

#include "TabelaVerdade.h"

using namespace std;
namespace testes = TestesTabelaVerdade;

void testes::executa() {
  cout << "=== TestesTabelaVerdade ===" << endl;
  deve_ser_capaz_de_gerar_tv_tabela_verdade();
}

void testes::deve_ser_capaz_de_gerar_tv_tabela_verdade() {
  cout << "deve_ser_capaz_de_gerar_tv_tabela_verdade" << endl;

  const std::string expr = "p ^ q v r v p ^ z";
  TTabelaVerdade tv(expr);
  if (tv.Monta()) {
    cout << tv.Stringify();
  }

  cout << endl;
}
