#include "FabricaProposicoes.h"

#include "AnalisadorLexico.h"

TVetorInsumosProposicoes
TFabricaProposicoes::Fabrica(const std::string &expr) const {
  TVetorInsumosProposicoes vec;

  const std::vector<TInsumoFabricaProposicao> insumos = GeraInsumos(expr);
  for (const TInsumoFabricaProposicao &insumo : insumos) {
    if (IProposicao *prop = _fabricaProposicao.Fabrica(insumo)) {
      auto insumocpy = new TInsumoFabricaProposicao(insumo);
      vec.StdVector().push_back(new TInsumoProposicao(insumocpy, prop));
    }
  }

  return vec;
}

std::vector<TInsumoFabricaProposicao>
TFabricaProposicoes::GeraInsumos(const std::string &expr) const {
  std::vector<TInsumoFabricaProposicao> insumos;

  std::vector<std::string> idProps = IdentificadoresProposicoes(expr);
  TArvoreBinaria<bool> combsTV = GeraCombinacoesTabelaVerdade(idProps.size());

  for (TNoArvoreBinaria<bool> *noFolha : combsTV.NosFolha()) {
    const std::vector<bool> combTV = combsTV.DadosOrdenadosRaizAoNo(noFolha);

    TInsumoFabricaProposicao insumo(expr);

    for (int i = 0; i < idProps.size(); i++) {
      const std::string &idProp = idProps[i];
      const bool &valorLogico = combTV[i];

      insumo.DefineValorLogico(idProp, valorLogico);
    }

    insumos.push_back(insumo);
  }

  return insumos;
}

TArvoreBinaria<bool>
TFabricaProposicoes::GeraCombinacoesTabelaVerdade(size_t entradas) const {
  TArvoreBinaria<bool> combinacoesTV;

  for (int i = 0; i < entradas; i++) {
    if (combinacoesTV.Vazia()) {
      auto noEsq = new TNoArvoreBinaria<bool>(true);
      auto noDir = new TNoArvoreBinaria<bool>(false);
      combinacoesTV.InsereFilhos(noEsq, noDir);
    } else {
      std::vector<TNoArvoreBinaria<bool> *> folhas = combinacoesTV.NosFolha();
      for (TNoArvoreBinaria<bool> *folha : folhas) {
        auto noEsq = new TNoArvoreBinaria<bool>(true, folha);
        auto noDir = new TNoArvoreBinaria<bool>(false, folha);
        folha->InsereFilhos(noEsq, noDir);
      }
    }
  }

  return combinacoesTV;
}

std::vector<std::string>
TFabricaProposicoes::IdentificadoresProposicoes(const std::string &expr) const {
  std::vector<std::string> identificadoresProps;

  auto TemItem = [&identificadoresProps](const std::string &identificador) {
    for (int i = 0; i < identificadoresProps.size(); i++) {
      if (identificadoresProps[i] == identificador) {
        return true;
      }
    }

    return false;
  };

  // se chamar direto TAnalisadorLexico().GeraListaTokens(expr).RawVector()
  // no for loop ranged base, quando pegar o RawVector o TokenVector nao
  // eh mais necessario, dai eh deletado e o RawVector aponta para
  // dangling pointers. Por isso separa a chamada, para manter o ciclo
  // de vida ate o fim do escopo
  TTokenVector tokens = TAnalisadorLexico().GeraListaTokens(expr);
  for (TToken *t : tokens.RawVector()) {
    if (t->TipoToken() == ETipoToken::PROPOSICAO) {
      if (!TemItem(t->Token())) {
        identificadoresProps.push_back(t->Token());
      }
    }
  }

  return identificadoresProps;
}
