#include "soda/parser.hpp"

#include <sstream>

#include "soda/logging.hpp"

namespace soda {

Parser::Parser(const std::vector<Token> &tokens)
    : m_tokens{tokens}, m_current_token{tokens.data()} {
  if (tokens.back().kind != TokenKind::EndOfFile) {
    soda::log_fatal("token stream must be terminated by TokenKind::EndOfFile\n");
  }
}

Token Parser::advance() {
  // Safety: The constructor ensures that the token stream is terminated with an end of file token,
  // so token consumption should never be unsafe.
  const Token &token = *m_current_token;
  if (m_current_token->kind != TokenKind::EndOfFile) {
    m_current_token++;
  }
  return token;
}

Token Parser::expect_token(TokenKind kind) {
  if (m_current_token->kind != kind) {
    std::ostringstream stream;
    stream << m_current_token->kind;
    soda::log_fatal("expected '%s'\n", stream.str().c_str());
  } else {
    return advance();
  }
}

Expression Parser::parse_expression() {
  switch (m_current_token->kind) {
  case TokenKind::Identifier:
    return parse_identifier();
  case TokenKind::Number:
    return parse_integer_literal();
  default:
    soda::log_fatal("expected expression");
  }
}

Identifier Parser::parse_identifier() {
  Token token = advance();
  if (token.kind == TokenKind::Identifier) {
    return Identifier{token.lexeme};
  } else {
    soda::log_fatal("expected identifier");
  }
}

IntegerLiteral Parser::parse_integer_literal() {
  Token token = advance();
  if (token.kind == TokenKind::Number) {
    std::int32_t value = std::stoi(token.lexeme);
    return IntegerLiteral{value};
  } else {
    soda::log_fatal("expected integer literal");
  }
}

Statement Parser::parse_statement() {
  switch (m_current_token->kind) {
  case TokenKind::BraceLeft:
    return parse_block_statement();
  case TokenKind::Return:
    return parse_return_statement();
  default:
    soda::log_fatal("expected statement");
  }
}

BlockStatement Parser::parse_block_statement() {
  expect_token(TokenKind::BraceLeft);
  std::vector<Statement> statements;
  while (m_current_token->kind != TokenKind::BraceRight) {
    Statement stmt = parse_statement();
    statements.push_back(stmt);
  }
  return BlockStatement{statements};
}

ReturnStatement Parser::parse_return_statement() {
  expect_token(TokenKind::Return);
  Expression return_value = parse_expression();
  expect_token(TokenKind::Semicolon);
  return ReturnStatement{return_value};
}

FunctionDeclaration Parser::parse_function_declaration() {
  expect_token(TokenKind::Fn);
  std::string name = expect_token(TokenKind::Identifier).lexeme;
  expect_token(TokenKind::ParenLeft);
  expect_token(TokenKind::ParenRight); // For now, don't parse args
  BlockStatement body = parse_block_statement();
  return FunctionDeclaration{
      name,
      std::nullopt,
      std::vector<TypedIdentifier>{},
      body,
  };
}

} // namespace soda
