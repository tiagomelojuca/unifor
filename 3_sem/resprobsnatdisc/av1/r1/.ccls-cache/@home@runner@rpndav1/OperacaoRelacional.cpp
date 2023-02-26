#include "OperacaoRelacional.h"

bool TOperacaoRelacional::Executa(bool p, bool q) const {
  if (_operacao == EOperadorRelacional::CONJUNCAO) {
    return p && q;
  } else if (_operacao == EOperadorRelacional::DISJUNCAO) {
    return p || q;
  } else if (_operacao == EOperadorRelacional::CONDICIONAL) {
    return !p || q;
  } else if (_operacao == EOperadorRelacional::BICONDICIONAL) {
    return p == q;
  }

  return false;
}