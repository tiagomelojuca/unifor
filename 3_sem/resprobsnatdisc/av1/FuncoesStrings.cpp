#include "FuncoesStrings.h"

#include <algorithm>

std::string FuncoesStrings::RemoverWhitespaces(const std::string &str) {
  std::string s = str;
  s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());

  return s;
}

std::pair<std::string, std::string>
FuncoesStrings::SeparaPrimeiro(const std::string &str,
                               const std::string &delimitador) {
  const std::size_t pos = str.find(delimitador);

  if (pos == std::string::npos) {
    return std::make_pair(str, "");
  }

  const std::string lhs = str.substr(0, pos);
  const std::string rhs = str.substr(pos + delimitador.length());

  return std::make_pair(lhs, rhs);
}

std::pair<std::string, std::string>
FuncoesStrings::SeparaUltimo(const std::string &str,
                             const std::string &delimitador) {
  const size_t tamDelimit = delimitador.length();
  std::string s = str;

  size_t prev_pos = std::string::npos;
  size_t pos = str.find(delimitador);

  while (pos != std::string::npos) {
    prev_pos = pos;
    const size_t _p = str.substr(pos + tamDelimit).find(delimitador);
    pos = _p == std::string::npos ? std::string::npos : pos + tamDelimit + _p;
  }

  if (prev_pos == std::string::npos) {
    return std::make_pair("", str);
  }

  const std::string lhs = str.substr(0, prev_pos);
  const std::string rhs = str.substr(prev_pos + tamDelimit);

  return std::make_pair(lhs, rhs);
}