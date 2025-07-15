#ifndef SODA_PARSER_HPP
#define SODA_PARSER_HPP

#include <stdexcept>
#include <vector>

#include "soda/ast.hpp"
#include "soda/token.hpp"

namespace soda::parser {

  class ParseError : public std::runtime_error {
  public:
    ParseError(const std::string &what_arg);
  };

  class Parser {
  public:
    explicit Parser(const std::vector<token::Token> &tokens);

    void consume_token();

    std::unique_ptr<ast::Expression> parse_identifier();
    std::unique_ptr<ast::Expression> parse_integer_literal();

    std::unique_ptr<ast::Statement> parse_block_statement();
    std::unique_ptr<ast::Statement> parse_return_statement();

    std::unique_ptr<ast::Declaration> parse_function_declaration();

  private:
    std::vector<token::Token> m_tokens;
    const token::Token *m_current_token = nullptr;
  };

}

#endif
