#ifndef OPERACAORELACIONAL_H_
#define OPERACAORELACIONAL_H_

// esclarecimento: o nome nao faz jus ao sentido comumente adotado
// na programacao, utiliza-se aqui a nomenclatura da Logica Proposicional,
// correspondendo, pois, as operacoes relacionais entre PROPOSICOES, nao
// entre numeros, motivo pelo qual assim chamamos na programacao.
// Seria analogo ao que chamamos de "Operadores Logicos" na programacao,
// pois trata das relacoes entre expressoes booleanas.

enum class EOperadorRelacional {
  INVALIDO,
  CONJUNCAO,
  DISJUNCAO,
  CONDICIONAL,
  BICONDICIONAL
};

class TOperacaoRelacional {
public:
  TOperacaoRelacional() = delete;
  TOperacaoRelacional(EOperadorRelacional op) : _operacao(op) {}

  bool Executa(bool p, bool q) const;

private:
  EOperadorRelacional _operacao;
};

#endif // OPERACAORELACIONAL_H_