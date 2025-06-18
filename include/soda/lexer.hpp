#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "soda/token.hpp"

namespace soda {

class Lexer {
public:
  explicit Lexer(std::string_view source);

  void skip_whitespace();
  Token next_token();

private:
  std::string::const_iterator m_it;
  std::string::const_iterator m_end;
};

std::vector<Token> tokenize_source(std::string_view source);

} // namespace soda
