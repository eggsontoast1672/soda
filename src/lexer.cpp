#include "soda/lexer.hpp"

#include <sstream>

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

static bool is_ident_start(char c) { return std::isalpha(c) || c == '_'; }
static bool is_ident(char c) { return is_ident_start(c) || std::isdigit(c); }

namespace soda::lexer {

  LexError::LexError(const char *source, std::size_t line, std::size_t column)
      : m_source{source}, m_line{line}, m_column{column} {
    // FIXME this might be a little inefficient, we can make it better later
    std::ostringstream stream;
    stream << "line " << m_line << ", column " << m_column
           << ": unrecognized character '@'";
    m_message = stream.str();
  }

  Lexer::Lexer(const std::filesystem::path &file) {
    throw std::runtime_error{"todo"};
  }

  std::optional<Token> Lexer::next_token() {
    if (m_position >= m_source.size()) {
      return std::nullopt;
    }

    skip_whitespace();

    m_start = m_position;

    char next = m_source[m_position];
    m_position += 1;
    switch (next) {
      // clang-format off
    case '{': return make_token(TokenKind::BraceLeft);
    case '}': return make_token(TokenKind::BraceRight);
    case '(': return make_token(TokenKind::ParenLeft);
    case ')': return make_token(TokenKind::ParenRight);
    case ';': return make_token(TokenKind::Semicolon);
      // clang-format on

    default:
      if (std::isdigit(next)) {
        return make_number();
      } else if (is_ident_start(next)) {
        return make_identifier();
      } else {
        throw LexError{"", 0, 0};
      }
    }
  }

  Token Lexer::make_identifier() {
    while (m_position < m_source.size() && is_ident(m_source[m_position])) {
      m_position += 1;
    }
    std::string lexeme = m_source.substr(m_start, m_position - m_start);
    TokenKind kind = identifier_kind(lexeme);
    return Token{kind, lexeme};
  }

  Token Lexer::make_number() {
    while (m_position < m_source.size() && std::isdigit(m_source[m_position])) {
      m_position += 1;
    }
    return make_token(TokenKind::Number);
  }

  Token Lexer::make_token(TokenKind kind) const {
    return Token {
      .kind = kind,
      .lexeme = m_source.substr(m_start, m_position - m_start),
      .line = m_line,
      .column = m_column,
    };
  }

  void Lexer::skip_whitespace() {
    while (m_position < m_source.size() && std::isspace(m_source[m_position])) {
      m_position += 1;
    }
  }

  std::vector<Token> tokenize_source(std::string_view source) {
    Lexer lexer{source};
    std::vector<Token> tokens;
    while (true) {
      std::optional<Token> token = lexer.next_token();
      if (token.has_value()) {
        tokens.push_back(token.value());
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

}
