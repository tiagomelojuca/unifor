#include "GerenciadorExecucao.h"

#include "CalculadoraProposicional.h"
#include "SuiteTestes.h"

void TGerenciadorExecucao::Executa() const {
  if (_ordemDeExecucao == EChaveamentoExecucao::EXECUTA_TESTES) {
    ExecutaSuiteTestes();
  } else if (_ordemDeExecucao == EChaveamentoExecucao::EXECUTA_APLICACAO) {
    ExecutaCalculadora();
  }
}

void TGerenciadorExecucao::ExecutaSuiteTestes() const {
  SuiteTestes::Executa();
}

void TGerenciadorExecucao::ExecutaCalculadora() const {
  TCalculadoraProposicional calc;
  calc.Executa();
}
