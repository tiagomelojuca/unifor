#ifndef FUNCOESSTRINGS_H_
#define FUNCOESSTRINGS_H_

#include <string>
#include <utility>

namespace FuncoesStrings {
std::string RemoverWhitespaces(const std::string &str);

std::pair<std::string, std::string>
SeparaPrimeiro(const std::string &str, const std::string &delimitador);

std::pair<std::string, std::string>
SeparaUltimo(const std::string &str, const std::string &delimitador);
} // namespace FuncoesStrings

#endif // FUNCOESSTRINGS_H_
