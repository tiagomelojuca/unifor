#ifndef PROPOSICAO_H_
#define PROPOSICAO_H_

#include "OperacaoRelacional.h"

class IProposicao {
public:
  virtual ~IProposicao() = default;
  virtual bool ValorLogico() const = 0;
};

class TProposicaoSimples : public IProposicao {
public:
  TProposicaoSimples() = delete;
  TProposicaoSimples(bool valorLogico) : _valorLogico(valorLogico) {}

  bool ValorLogico() const override { return _valorLogico; }

private:
  bool _valorLogico;
};

class TProposicaoComposta : public IProposicao {
public:
  TProposicaoComposta() = delete;
  TProposicaoComposta(const IProposicao *p, const IProposicao *q,
                      EOperadorRelacional op)
      : _p(p), _q(q), _opRel(op) {}

  bool ValorLogico() const override {
    const bool vl_p = _p->ValorLogico();
    const bool vl_q = _q->ValorLogico();
    return TOperacaoRelacional(_opRel).Executa(vl_p, vl_q);
  }

  ~TProposicaoComposta() {
    delete _p;
    delete _q;
  }

private:
  const IProposicao *_p;
  const IProposicao *_q;

  EOperadorRelacional _opRel;
};

#endif // PROPOSICAO_H_