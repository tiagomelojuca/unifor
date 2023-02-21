#ifndef OPERACAORELACIONAL_H_
#define OPERACAORELACIONAL_H_

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