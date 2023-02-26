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

        return new TProposicaoSimples(p);
      }
    }
  }

  return nullptr;
}

IProposicao *TFabricaProposicao::FabricaProposicaoComposta(
    const TInsumoFabricaProposicao &entrada,
    const std::vector<TToken *> &tokens, ELexemes lexeme) const {
  if (lexeme != ELexemes::CONJUNCAO && lexeme != ELexemes::DISJUNCAO &&
      lexeme != ELexemes::CONDICIONAL && lexeme != ELexemes::BICONDICIONAL) {
    return nullptr;
  }

  const size_t posLex = TTokenVector::BuscaPrimeiraOcorrencia(tokens, lexeme);
  if (posLex == SIZE_MAX) {
    return nullptr;
  }

  const size_t posPrecedI = TTokenVector::BuscaPrimeiraOcorrencia(
      tokens, ELexemes::PRECEDENCIA_INICIO);
  const size_t posPrecedF =
      TTokenVector::BuscaUltimaOcorrencia(tokens, ELexemes::PRECEDENCIA_FIM);
  if (posLex > posPrecedI && posLex < posPrecedF) {
    return nullptr;
  }

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

  if (operador == EOperadorRelacional::INVALIDO) {
    return nullptr;
  }

  std::string lhs = "";
  for (int i = 0; i < posLex; i++) {
    lhs += tokens[i]->Token();
  }

  std::string rhs = "";
  for (int i = posLex + 1; i < tokens.size(); i++) {
    rhs += tokens[i]->Token();
  }

  IProposicao *p1 = Fabrica(FabricaInsumoFilho(lhs, entrada));
  IProposicao *p2 = Fabrica(FabricaInsumoFilho(rhs, entrada));

  return new TProposicaoComposta(p1, p2, operador);
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