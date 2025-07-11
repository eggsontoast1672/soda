#pragma once

#include <stdexcept>
#include <vector>

#include "soda/ast.hpp"
#include "soda/token.hpp"

namespace soda {
  class ParseError : public std::runtime_error {
  public:
    ParseError(const std::string &what_arg);
  };

  class Parser {
  public:
    explicit Parser(const std::vector<Token> &tokens);

    Token consume(TokenKind expected, const std::string &message);
    Program program();
    ReturnStatement return_statement();

  private:
    std::vector<Token> m_tokens;
    std::size_t m_pos = 0;
  };

  Program parse_source(std::string_view source);
  Program parse_tokens(const std::vector<Token> &tokens);
}
