#include "soda/lexer.hpp"

#include <sstream>
#include <stdexcept>

static std::string escape(char c) {
  switch (c) {
  case '\a':
    return "\\a";
  case '\b':
    return "\\b";
  case '\f':
    return "\\f";
  case '\n':
    return "\\n";
  case '\r':
    return "\\r";
  case '\t':
    return "\\t";
  case '\v':
    return "\\v";
  case '\?':
    return "\\?";
  case '\0':
    return "\\0";
  default:
    return std::string{c};
  }
}

namespace soda {

LexError::LexError(const char *source, std::size_t line, std::size_t column)
    : m_source{source}, m_line{line}, m_column{column} {
  // FIXME this might be a little inefficient, we can make it better later
  std::ostringstream stream;
  stream << "line " << m_line << ", column " << m_column
         << ": unrecognized character '@'";
  m_message = stream.str();
}

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
      Token token = {
          .lexeme = std::string{*m_it},
          .line = 1,
          .column = 1,
      };
      throw LexError{"", 0, 0};
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

void print_lexer_error(const LexError &error) {
  // Problem: we need access to the source code
  // Solution 1: LexError stores a pointer to the source code, along with the
  // line and column of the offending character.
}

} // namespace soda
