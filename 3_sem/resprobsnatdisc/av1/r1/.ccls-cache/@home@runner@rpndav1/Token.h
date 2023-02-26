#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <vector>

#include "TabelaLexemes.h"

enum class ETipoToken {
  INVALIDO,
  PROPOSICAO,
  OPERACAO_UNARIA,
  OPERACAO_BINARIA,
  ESPECIFICADOR_PRECEDENCIA_I,
  ESPECIFICADOR_PRECEDENCIA_F
};

class TToken {
public:
  TToken() = delete;
  TToken(const std::string &token, ETipoToken tipoToken);

  const std::string &Token() const;
  ETipoToken TipoToken() const;

  TToken *TokenAnterior() const;
  TToken *TokenCorrente() const;
  TToken *TokenSeguinte() const;

  void TokenAnterior(TToken *anterior);
  void TokenSeguinte(TToken *seguinte);

private:
  std::string _token;
  ETipoToken _tipoToken;

  TToken *_anterior = nullptr;
  TToken *_corrente = nullptr;
  TToken *_seguinte = nullptr;
};

class TTokenVector {
public:
  TTokenVector() = default;
  virtual ~TTokenVector();

  void PushToken(const TToken &token);
  TToken *Begin() const;
  TToken *End() const;
  const std::vector<TToken *> &RawVector() const;

  static size_t BuscaPrimeiraOcorrencia(const std::vector<TToken *> &tokens,
                                        ETipoToken tipo);
  static size_t BuscaUltimaOcorrencia(const std::vector<TToken *> &tokens,
                                      ETipoToken tipo);

  static size_t BuscaPrimeiraOcorrencia(const std::vector<TToken *> &tokens,
                                        ELexemes lexeme);
  static size_t BuscaUltimaOcorrencia(const std::vector<TToken *> &tokens,
                                      ELexemes lexeme);
  static size_t Conta(const std::vector<TToken *> &tokens, ELexemes lexeme);

  static std::vector<TToken *>
  TokensAEsquerda(const std::vector<TToken *> &tokens, size_t pos);

  static std::vector<TToken *>
  TokensADireita(const std::vector<TToken *> &tokens, size_t pos);

private:
  std::vector<TToken *> _tokens;
};

#endif // TOKEN_H_