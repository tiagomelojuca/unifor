#include "CalculadoraProposicional.h"

#include <iostream>

#include "TabelaVerdade.h"

static const std::string msgErro = "ERRO: expr invalida!";

void TCalculadoraProposicional::Executa() const {
  std::cout << "Digite uma proposição: ";

  std::string p;
  std::getline(std::cin, p);

  TTabelaVerdade tv(p);
  const bool montagemOk = tv.Monta();
  const std::string output = montagemOk ? tv.Stringify() : msgErro;

  std::cout << std::endl << output << std::endl;
}
