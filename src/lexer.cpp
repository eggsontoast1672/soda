#include "soda/lexer.hpp"

#include <sstream>
#include <stdexcept>

namespace soda {

Lexer::Lexer(std::string_view source)
    : m_it{source.begin()}, m_end{source.end()} {}

void Lexer::skip_whitespace() {
  while (m_it != m_end && std::isspace(*m_it)) {
    m_it++;
  }
}

Token Lexer::next_token() {
  if (m_it == m_end) {
    return {TokenKind::EndOfFile, ""};
  }

  skip_whitespace();

  switch (*m_it) {
  case '{':
    m_it++;
    return {TokenKind::BraceLeft, "{"};
  case '}':
    m_it++;
    return {TokenKind::BraceRight, "}"};
  case '(':
    m_it++;
    return {TokenKind::ParenLeft, "("};
  case ')':
    m_it++;
    return {TokenKind::ParenRight, ")"};
  case ';':
    m_it++;
    return {TokenKind::Semicolon, ";"};
  default:
    if (std::isdigit(*m_it)) {
      std::string lexeme;
      lexeme.push_back(*m_it);
      m_it++;
      while (m_it != m_end && std::isdigit(*m_it)) {
        lexeme.push_back(*m_it);
        m_it++;
      }
      return {TokenKind::Number, lexeme};
    } else if (std::isalpha(*m_it) || *m_it == '_') {
      std::string lexeme;
      lexeme.push_back(*m_it);
      m_it++;
      while (m_it != m_end && (std::isalnum(*m_it) || *m_it == '_')) {
        lexeme.push_back(*m_it);
        m_it++;
      }
      TokenKind kind = identifier_kind(lexeme);
      return {kind, lexeme};
    } else {
      std::ostringstream s;
      s << "unknown token: '" << *m_it << "'";
      throw std::runtime_error{s.str()};
    }
  }
}

std::vector<Token> tokenize_source(std::string_view source) {
  Lexer lexer{source};
  std::vector<Token> tokens;
  while (true) {
    Token token = lexer.next_token();
    if (token.kind != TokenKind::EndOfFile) {
      tokens.push_back(token);
    } else {
      break;
    }
  }
  return tokens;
}

} // namespace soda
