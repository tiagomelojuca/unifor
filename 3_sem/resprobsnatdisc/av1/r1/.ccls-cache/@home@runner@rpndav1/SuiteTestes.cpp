#include "SuiteTestes.h"

#include "TestesAnalisadorLexico.h"
#include "TestesAnalisadorSintatico.h"
#include "TestesFabricaProposicao.h"
#include "TestesFabricaProposicoes.h"
#include "TestesFuncoesStrings.h"
#include "TestesTabelaLexemes.h"
#include "TestesTabelaVerdade.h"

void SuiteTestes::Executa() {
  ExecutaTestesFuncoesStrings();
  ExecutaTestesTabelaLexemes();
  ExecutaTestesAnalisadorLexico();
  ExecutaTestesAnalisadorSintatico();
  ExecutaTestesFabricaProposicao();
  ExecutaTestesFabricaProposicoes();
  ExecutaTestesTabelaVerdade();
}

void SuiteTestes::ExecutaTestesFuncoesStrings() {
  TestesFuncoesStrings::executa();
}

void SuiteTestes::ExecutaTestesTabelaLexemes() {
  TestesTabelaLexemes::executa();
}

void SuiteTestes::ExecutaTestesAnalisadorLexico() {
  TestesAnalisadorLexico::executa();
}

void SuiteTestes::ExecutaTestesAnalisadorSintatico() {
  TestesAnalisadorSintatico::executa();
}

void SuiteTestes::ExecutaTestesFabricaProposicao() {
  TestesFabricaProposicao::executa();
}

void SuiteTestes::ExecutaTestesFabricaProposicoes() {
  TestesFabricaProposicoes::executa();
}

void SuiteTestes::ExecutaTestesTabelaVerdade() {
  TestesTabelaVerdade::executa();
}
