#ifndef GERENCIADOREXECUCAO_H_
#define GERENCIADOREXECUCAO_H_

enum class EChaveamentoExecucao { EXECUTA_TESTES, EXECUTA_APLICACAO };

// outras sugestoes de nome: TExecutor
class TGerenciadorExecucao {
public:
  TGerenciadorExecucao() = delete;
  explicit TGerenciadorExecucao(EChaveamentoExecucao ordemExecucao)
      : _ordemDeExecucao(ordemExecucao) {}

  void Executa() const;

private:
  void ExecutaSuiteTestes() const;
  void ExecutaCalculadora() const;

  EChaveamentoExecucao _ordemDeExecucao;
  // sentido de ordenar, comando; nao de arranjo no conjunto
};

#endif // GERENCIADOREXECUCAO_H_
