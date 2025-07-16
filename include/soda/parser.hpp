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

  std::unique_ptr<Expression> parse_expression();
  std::unique_ptr<Expression> parse_identifier();
  std::unique_ptr<Expression> parse_integer_literal();

  std::unique_ptr<Statement> parse_statement();
  std::unique_ptr<Statement> parse_block_statement();
  std::unique_ptr<Statement> parse_return_statement();

  std::unique_ptr<Declaration> parse_function_declaration();

private:
  std::vector<Token> m_tokens;
  const Token *m_current_token = nullptr;
};

} // namespace soda

#endif
