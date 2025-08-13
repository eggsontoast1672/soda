#ifndef SODA_PARSER_HPP
#define SODA_PARSER_HPP

#include <vector>

#include "soda/ast.hpp"
#include "soda/token.hpp"

namespace soda {

class Parser {
public:
  explicit Parser(const std::vector<Token> &tokens);

  Token advance();
  Token expect_token(TokenKind kind);

  Expression parse_expression();
  Identifier parse_identifier();
  IntegerLiteral parse_integer_literal();

  Statement parse_statement();
  BlockStatement parse_block_statement();
  ReturnStatement parse_return_statement();

  FunctionDeclaration parse_function_declaration();

private:
  std::vector<Token> m_tokens;
  const Token *m_current_token = nullptr;
};

} // namespace soda

#endif
