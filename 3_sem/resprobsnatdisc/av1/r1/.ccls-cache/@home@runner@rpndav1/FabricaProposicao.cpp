#include "FabricaProposicao.h"

TInsumoFabricaProposicao::TInsumoFabricaProposicao(const std::string &expr)
    : _expressao(expr) {}

const std::string &TInsumoFabricaProposicao::Expressao() const {
  return _expressao;
}

void TInsumoFabricaProposicao::DefineValorLogico(
    const std::string &identificador, bool valorLogico) {
  _valoresLogicos[identificador] = valorLogico;
}

bool TInsumoFabricaProposicao::PossuiValorLogico(
    const std::string &identificador) const {
  return _valoresLogicos.find(identificador) != _valoresLogicos.end();
}

bool TInsumoFabricaProposicao::ValorLogico(
    const std::string &identificador) const {
  return _valoresLogicos.find(identificador)->second;
}

std::vector<std::string>
TInsumoFabricaProposicao::IdentificadoresProposicoes() const {
  std::vector<std::string> identificadores;

  for (auto it = _valoresLogicos.begin(); it != _valoresLogicos.end(); ++it) {
    identificadores.push_back(it->first);
  }

  return identificadores;
}

IProposicao *
TFabricaProposicao::Fabrica(const TInsumoFabricaProposicao &entrada) const {
  TTokenVector tokens = _analisadorLexico.GeraListaTokens(entrada.Expressao());

  if (!_analisadorSintatico.Verifica(tokens)) {
    return nullptr;
  }

  auto identificadoresProposicoes = FiltraIdentificadores(tokens);
  for (TToken *identificadorProposicao : identificadoresProposicoes) {
    if (!entrada.PossuiValorLogico(identificadorProposicao->Token())) {
      return nullptr;
    }
  }

  return Fabrica(entrada, tokens.RawVector());
}

IProposicao *
TFabricaProposicao::Fabrica(const TInsumoFabricaProposicao &entrada,
                            const std::vector<TToken *> &tokens) const {
  if (auto proposicao = FabricaProposicaoSimples(entrada, tokens)) {
    return proposicao;
  }

  if (auto proposicao =
          FabricaProposicaoComposta(entrada, tokens, ELexemes::BICONDICIONAL)) {
    return proposicao;
  }

  if (auto proposicao =
          FabricaProposicaoComposta(entrada, tokens, ELexemes::CONDICIONAL)) {
    return proposicao;
  }

  if (auto proposicao =
          FabricaProposicaoComposta(entrada, tokens, ELexemes::DISJUNCAO)) {
    return proposicao;
  }

  if (auto proposicao =
          FabricaProposicaoComposta(entrada, tokens, ELexemes::CONJUNCAO)) {
    return proposicao;
  }

  if (auto proposicao = FabricaProposicaoFilha(entrada, tokens)) {
    return proposicao;
  }

  return nullptr;
}

IProposicao *TFabricaProposicao::FabricaProposicaoSimples(
    const TInsumoFabricaProposicao &entrada,
    const std::vector<TToken *> &tokens) const {
  const size_t posOperacao = TTokenVector::BuscaPrimeiraOcorrencia(
      tokens, ETipoToken::OPERACAO_BINARIA);

  const size_t posPrecedI = TTokenVector::BuscaPrimeiraOcorrencia(
      tokens, ETipoToken::ESPECIFICADOR_PRECEDENCIA_I);

  if (posOperacao == SIZE_MAX && posPrecedI == SIZE_MAX) {
    for (TToken *token : tokens) {
      if (token->TipoToken() == ETipoToken::PROPOSICAO) {
        bool p = entrada.ValorLogico(token->Token());

        if (DeveAplicarNegacao(*token)) {
          p = !p;
        }

        auto _p = new TProposicaoSimples(p);
        _p->Label(token->Token());

        return _p;
      }
    }
  }

  return nullptr;
}

IProposicao *TFabricaProposicao::FabricaProposicaoComposta(
    const TInsumoFabricaProposicao &entrada,
    const std::vector<TToken *> &tokens, ELexemes lexeme) const {
  const EOperadorRelacional operador = Lexeme2Operador(lexeme);
  if (operador == EOperadorRelacional::INVALIDO) {
    return nullptr;
  }

  const size_t posLex = BuscaLexemeTopLevel(tokens, lexeme);
  if (posLex == SIZE_MAX) {
    return nullptr;
  }

  std::string lhs = Stringify(TTokenVector::TokensAEsquerda(tokens, posLex));
  std::string rhs = Stringify(TTokenVector::TokensADireita(tokens, posLex));

  IProposicao *p1 = Fabrica(FabricaInsumoFilho(lhs, entrada));
  IProposicao *p2 = Fabrica(FabricaInsumoFilho(rhs, entrada));

  auto p = new TProposicaoComposta(p1, p2, operador);
  p->LabelP(lhs);
  p->LabelQ(rhs);

  return p;
}

IProposicao *TFabricaProposicao::FabricaProposicaoFilha(
    const TInsumoFabricaProposicao &entrada,
    const std::vector<TToken *> &tokens) const {
  const std::string lexI = _tabelaLexemes.Lexeme(ELexemes::PRECEDENCIA_INICIO);
  const std::string lexF = _tabelaLexemes.Lexeme(ELexemes::PRECEDENCIA_FIM);

  if (tokens.front()->Token() == lexI && tokens.back()->Token() == lexF) {
    std::string subexpr = "";
    for (int i = 1; i < tokens.size() - 1; i++) {
      subexpr += tokens[i]->Token();
    }

    return Fabrica(FabricaInsumoFilho(subexpr, entrada));
  }

  const std::string lexNeg = _tabelaLexemes.Lexeme(ELexemes::NEGACAO);
  if (tokens.front()->Token() == lexNeg) {
    std::string subexpr = "";
    for (int i = 1; i < tokens.size(); i++) {
      subexpr += tokens[i]->Token();
    }

    return new TProposicaoNegada(Fabrica(FabricaInsumoFilho(subexpr, entrada)));
  }

  return nullptr;
}

TInsumoFabricaProposicao TFabricaProposicao::FabricaInsumoFilho(
    const std::string &subexpr, const TInsumoFabricaProposicao &parent) const {
  TInsumoFabricaProposicao subInsumo(subexpr);

  TTokenVector tokensSubInsumo = _analisadorLexico.GeraListaTokens(subexpr);
  auto props = FiltraIdentificadores(tokensSubInsumo); // proposicoes

  for (TToken *prop : props) {
    const std::string &t = prop->Token();
    subInsumo.DefineValorLogico(t, parent.ValorLogico(t));
  }

  return subInsumo;
}

bool TFabricaProposicao::DeveAplicarNegacao(const TToken &token) const {
  const std::string lexemeNegacao = _tabelaLexemes.Lexeme(ELexemes::NEGACAO);

  bool aplicaNegacao = false;

  TToken *tokenAnterior = token.TokenAnterior();
  while (tokenAnterior != nullptr && tokenAnterior->Token() == lexemeNegacao) {
    aplicaNegacao = !aplicaNegacao;
    tokenAnterior = tokenAnterior->TokenAnterior();
  }

  return aplicaNegacao;
}

size_t
TFabricaProposicao::BuscaLexemeTopLevel(const std::vector<TToken *> &tokens,
                                        ELexemes lexeme) const {
  size_t posLex = TTokenVector::BuscaPrimeiraOcorrencia(tokens, lexeme);
  if (posLex == SIZE_MAX) {
    return SIZE_MAX;
  }

  std::vector<TToken *> tokensDir;
  bool ehTokenTopLevel = EhTokenTopLevel(tokens, posLex);
  while (!ehTokenTopLevel) {
    tokensDir = TTokenVector::TokensADireita(tokens, posLex);
    size_t pRel = TTokenVector::BuscaPrimeiraOcorrencia(tokensDir, lexeme);

    if (pRel == SIZE_MAX) {
      return SIZE_MAX;
    }

    const size_t offset = pRel + 1;
    posLex += offset;

    ehTokenTopLevel = EhTokenTopLevel(tokens, posLex);
  }

  return posLex;
}

bool TFabricaProposicao::EhTokenTopLevel(const std::vector<TToken *> &tokens,
                                         size_t posToken) const {
  const std::vector<TToken *> tokensEsq =
      TTokenVector::TokensAEsquerda(tokens, posToken);

  const size_t c1 =
      TTokenVector::Conta(tokensEsq, ELexemes::PRECEDENCIA_INICIO);
  const size_t c2 = TTokenVector::Conta(tokensEsq, ELexemes::PRECEDENCIA_FIM);

  return c1 == c2;
}

EOperadorRelacional TFabricaProposicao::Lexeme2Operador(ELexemes lexeme) const {
  EOperadorRelacional operador = EOperadorRelacional::INVALIDO;

  if (lexeme == ELexemes::CONJUNCAO) {
    operador = EOperadorRelacional::CONJUNCAO;
  } else if (lexeme == ELexemes::DISJUNCAO) {
    operador = EOperadorRelacional::DISJUNCAO;
  } else if (lexeme == ELexemes::CONDICIONAL) {
    operador = EOperadorRelacional::CONDICIONAL;
  } else if (lexeme == ELexemes::BICONDICIONAL) {
    operador = EOperadorRelacional::BICONDICIONAL;
  }

  return operador;
}

std::string
TFabricaProposicao::Stringify(const std::vector<TToken *> &tokens) const {
  std::string cadeia = "";

  for (const TToken *token : tokens) {
    cadeia += token->Token();
  }

  return cadeia;
}

std::vector<TToken *>
TFabricaProposicao::FiltraIdentificadores(const TTokenVector &tokens) const {
  std::vector<TToken *> tokensFiltrados;

  for (TToken *token : tokens.RawVector()) {
    if (token->TipoToken() == ETipoToken::PROPOSICAO) {
      tokensFiltrados.push_back(token);
    }
  }

  return tokensFiltrados;
}