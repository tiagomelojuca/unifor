#include "GerenciadorExecucao.h"

int main() {
  TGerenciadorExecucao executor(EChaveamentoExecucao::EXECUTA_APLICACAO);
  executor.Executa();

  return 0;
}
