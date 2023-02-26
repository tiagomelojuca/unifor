#ifndef PROPOSICAO_H_
#define PROPOSICAO_H_

#include <string>

#include "OperacaoRelacional.h"

class IProposicao {
public:
  virtual ~IProposicao() = default;

  virtual bool ValorLogico() const = 0;
  virtual std::string Label() const = 0;
};

class TProposicaoSimples : public IProposicao {
public:
  TProposicaoSimples() = delete;
  TProposicaoSimples(bool valorLogico);

  ~TProposicaoSimples() = default;

  bool ValorLogico() const override;
  std::string Label() const override;

  void Label(const std::string &label);

private:
  bool _valorLogico;
  std::string _label;
};

class TProposicaoComposta : public IProposicao {
public:
  TProposicaoComposta() = delete;
  TProposicaoComposta(const IProposicao *p, const IProposicao *q,
                      EOperadorRelacional op);

  ~TProposicaoComposta();

  bool ValorLogico() const override;
  std::string Label() const override;

  void LabelP(const std::string &label);
  void LabelQ(const std::string &label);

private:
  const IProposicao *_p;
  const IProposicao *_q;
  EOperadorRelacional _opRel;

  std::string _lbl_p;
  std::string _lbl_q;
};

// Sobre a classe TProposicaoNegada:
// Essa classe esta sendo criada por um mero artificio de codigo.
// Embora do ponto de vista do codigo seja uma classe irma das
// outras duas acima, ela nao eh equivalente/contraparte/complementar
// das duas classes criadas acima, que, por sua vez, sao, de fato,
// classificacoes formais de proposicoes. As classes nao sao irmas
// do ponto de vista semantico, apenas do ponto de vista hierarquico
// de codigo, atrelado ao mecanismo de heranca.
//
// A rigor, proposicoes sao classificadas em Simples ou Compostas
// A negacao, por outro lado, eh uma operacao aplicada sobre uma prop
// qualquer, seja ela simples ou composta. Ou seja, nao eh um conceito
// relacionado as outras duas supracitadas. Apesar disso, pro nosso codigo,
// convem ter uma casca sobre outra proposicao qualquer, seja ela simples
// ou composta, para respeitar a estrutura em arvore do codigo.
//
// Certamente existe alguma maneira melhor de organizar esse codigo,
// e centenas de abstracoes melhores. Mas eh so um exercicio da faculdade,
// e o prazo ta curto. Seria soh overengineering sem proposito.
class TProposicaoNegada : public IProposicao {
public:
  TProposicaoNegada() = delete;
  TProposicaoNegada(const IProposicao *p);

  ~TProposicaoNegada();

  bool ValorLogico() const override;
  std::string Label() const override;

private:
  const IProposicao *_p;
};

#endif // PROPOSICAO_H_