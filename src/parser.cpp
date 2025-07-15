#include "soda/parser.hpp"

#include "soda/lexer.hpp"

namespace soda::parser {

  using namespace ast;
  using namespace token;

  ParseError::ParseError(const std::string &what_arg)
      : std::runtime_error{what_arg} {}

  Parser::Parser(const std::vector<Token> &tokens)
    : m_tokens{tokens}, m_current_token{tokens.data()} {}

  void Parser::consume_token() {
    // For safety reasons, we do not want the current token pointer to advance
    // past the EndOfFile token.
    if (m_current_token->kind != TokenKind::EndOfFile) {
      m_current_token++;
    }
  }

  std::unique_ptr<Expression> Parser::parse_identifier() {
    if (m_current_token->kind == TokenKind::Identifier) {
      const std::string &name = m_current_token->lexeme;
      consume_token();
      return std::make_unique<Identifier>(name);
    } else {
      return nullptr;
    }
  }

  std::unique_ptr<Expression> Parser::parse_integer_literal() {
    if (m_current_token->kind == TokenKind::Number) {
      int32_t value = std::stoi(m_current_token->lexeme);
      consume_token();
      return std::make_unique<IntegerLiteral>(value);
    } else {
      return nullptr;
    }
  }

}
