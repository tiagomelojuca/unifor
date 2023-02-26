#include "Proposicao.h"

#include "TabelaLexemes.h"

TProposicaoSimples::TProposicaoSimples(bool valorLogico)
    : _valorLogico(valorLogico) {}

bool TProposicaoSimples::ValorLogico() const { return _valorLogico; }

std::string TProposicaoSimples::Label() const {
  std::string _lbl = "";

  _lbl += "[[";
  _lbl += _label;
  _lbl += "]]";

  return _lbl;
}

void TProposicaoSimples::Label(const std::string &label) { _label = label; }

TProposicaoComposta::TProposicaoComposta(const IProposicao *p,
                                         const IProposicao *q,
                                         EOperadorRelacional op)
    : _p(p), _q(q), _opRel(op) {}

TProposicaoComposta::~TProposicaoComposta() {
  delete _p;
  delete _q;
}

bool TProposicaoComposta::ValorLogico() const {
  const bool vl_p = _p->ValorLogico();
  const bool vl_q = _q->ValorLogico();
  return TOperacaoRelacional(_opRel).Executa(vl_p, vl_q);
}

std::string TProposicaoComposta::Label() const {
  std::string _label = "";

  _label += "[[";
  _label += _lbl_p;
  _label += "]]";
  _label += " ";

  TTabelaLexemes t;
  if (_opRel == EOperadorRelacional::CONJUNCAO) {
    _label += t.Lexeme(ELexemes::CONJUNCAO);
  } else if (_opRel == EOperadorRelacional::DISJUNCAO) {
    _label += t.Lexeme(ELexemes::DISJUNCAO);
  } else if (_opRel == EOperadorRelacional::CONDICIONAL) {
    _label += t.Lexeme(ELexemes::CONDICIONAL);
  } else if (_opRel == EOperadorRelacional::BICONDICIONAL) {
    _label += t.Lexeme(ELexemes::BICONDICIONAL);
  }

  _label += " ";
  _label += "[[";
  _label += _lbl_q;
  _label += "]]";

  return _label;
}

void TProposicaoComposta::LabelP(const std::string &label) { _lbl_p = label; }

void TProposicaoComposta::LabelQ(const std::string &label) { _lbl_q = label; }

TProposicaoNegada::TProposicaoNegada(const IProposicao *p) : _p(p) {}

TProposicaoNegada::~TProposicaoNegada() { delete _p; }

bool TProposicaoNegada::ValorLogico() const { return !_p->ValorLogico(); }

std::string TProposicaoNegada::Label() const {
  std::string _lbl = "";

  _lbl += "~";
  _lbl += "[[";
  _lbl += _p->Label();
  _lbl += "]]";

  return _lbl;
}