#include "TestesFabricaProposicoes.h"

#include <iostream>

#include "FabricaProposicoes.h"

using namespace std;
namespace testes = TestesFabricaProposicoes;

void testes::executa() {
  cout << "=== TestesFabricaProposicoes ===" << endl;
  deve_ser_capaz_de_gerar_todas_as_combinacoes_de_entrada_da_tabela_verdade();
}

void testes::
    deve_ser_capaz_de_gerar_todas_as_combinacoes_de_entrada_da_tabela_verdade() {
  cout << "deve_ser_capaz_de_gerar_todas_as_combinacoes_de_entrada_da_tabela_"
       << "verdade" << endl;

  TFabricaProposicoes fabrica;
  TVetorInsumosProposicoes pares = fabrica.Fabrica("p ^ q v r v p ^ z");

  for (const TInsumoProposicao *par : pares.StdVector()) {
    const bool vl = par->Proposicao().ValorLogico();
    std::cout << (vl ? "true" : "false") << std::endl;
  }

  cout << endl;
}
