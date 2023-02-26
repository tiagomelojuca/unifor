#include "TestesAnalisadorLexico.h"

#include <iostream>

#include "AnalisadorLexico.h"

using namespace std;
namespace testes = TestesAnalisadorLexico;

void testes::executa() {
  cout << "=== TestesAnalisadorLexico ===" << endl;
  deve_ser_capaz_de_parsear_tokens_de_uma_cadeia();
  deve_ser_capaz_de_gerar_lista_tokens_de_uma_cadeia();
}

void testes::deve_ser_capaz_de_parsear_tokens_de_uma_cadeia() {
  cout << "deve_ser_capaz_de_parsear_tokens_de_uma_cadeia" << endl;

  TAnalisadorLexico analisador;

  const std::string aspa = "\"";
  auto PrintTokens = [&analisador, &aspa](const std::string &expr) {
    const vector<string> tokens = analisador.ParseTokens(expr);
    cout << aspa << expr << aspa << " : [[ ";
    for (int i = 0; i < tokens.size(); i++) {
      const std::string &token = tokens[i];
      cout << aspa << token << aspa;

      if (i < tokens.size() - 1) {
        cout << ", ";
      }
    }
    cout << " ]]" << endl;
  };

  PrintTokens("p ^ q v ~(r <-> p)");
  PrintTokens("   pz ^ qf v ~(r v p) ");
  PrintTokens("(~a v b) ^ (b -> c) -> (a -> c)");
  PrintTokens("(p -> q) ^ ~p -> ~q");
  PrintTokens("p v ~(p ^ q)");
  PrintTokens("(p v q) ^ ~(p v q)");

  cout << endl;
}

void testes::deve_ser_capaz_de_gerar_lista_tokens_de_uma_cadeia() {
  cout << "deve_ser_capaz_de_gerar_lista_tokens_de_uma_cadeia" << endl;

  TAnalisadorLexico analisador;

  auto Str = [](const TToken *token) -> std::string {
    if (!token) {
      return "nullptr";
    }

    std::string strToken = "\"";
    strToken += token->Token();
    strToken += "\"";

    return strToken;
  };

  auto StrTipo = [](ETipoToken tipo) -> std::string {
    std::string strTipo = "\"";

    if (tipo == ETipoToken::INVALIDO) {
      strTipo += "INVALIDO";
    } else if (tipo == ETipoToken::PROPOSICAO) {
      strTipo += "PROPOSICAO";
    } else if (tipo == ETipoToken::OPERACAO_UNARIA) {
      strTipo += "OPERACAO_UNARIA";
    } else if (tipo == ETipoToken::OPERACAO_BINARIA) {
      strTipo += "OPERACAO_BINARIA";
    } else if (tipo == ETipoToken::ESPECIFICADOR_PRECEDENCIA_I) {
      strTipo += "ESPECIFICADOR_PRECEDENCIA_I";
    } else if (tipo == ETipoToken::ESPECIFICADOR_PRECEDENCIA_F) {
      strTipo += "ESPECIFICADOR_PRECEDENCIA_F";
    }

    strTipo += "\"";

    return strTipo;
  };

  auto PrintTokens = [&Str, &StrTipo, &analisador](const std::string &expr) {
    TTokenVector tokens = analisador.GeraListaTokens(expr);
    const std::string aspa = "\"";

    cout << "\ncadeia: " << aspa << expr << aspa << "," << endl;
    for (const TToken *token : tokens.RawVector()) {
      cout << "{" << endl;
      cout << "  token: " << aspa << token->Token() << aspa << "," << endl;
      cout << "  tipoToken: " << StrTipo(token->TipoToken()) << "," << endl;
      cout << "  anterior: " << Str(token->TokenAnterior()) << "," << endl;
      cout << "  corrente: " << Str(token->TokenCorrente()) << "," << endl;
      cout << "  seguinte: " << Str(token->TokenSeguinte()) << "," << endl;
      cout << "}," << endl;
    }
  };

  PrintTokens("   pz ^ qf v ~(r <-> p) ");
  PrintTokens("(~a v b) ^ (b -> c) -> (a -> c)");
  PrintTokens("(p -> q) ^ ~p -> ~q");
  PrintTokens("p v ~(p ^ q)");
  PrintTokens("(p v q) ^ ~(p v q)");

  cout << endl;
}