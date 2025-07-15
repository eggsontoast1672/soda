#include "soda/lexer.hpp"

#include <iostream>

static bool is_ident_start(char c) { return std::isalpha(c) || c == '_'; }
static bool is_ident(char c) { return is_ident_start(c) || std::isdigit(c); }

namespace soda::lexer {

  using namespace token;

  Lexer::Lexer(const std::string &source) : m_source{source} {}

  char Lexer::char_at(std::size_t index) {
    if (m_pos + index < m_source.size()) {
      return m_source[m_pos + index];
    } else {
      return '\0';
    }
  }

  char Lexer::consume_char() {
    char next = '\0';
    if (m_pos < m_source.size()) {
      next = m_source[m_pos];
      m_pos++;
      m_column++;
    }
    return next;
  }

  Token Lexer::get_next_token() {
    skip_whitespace();
    m_start = m_pos;
    char next = consume_char();
    switch (next) {
    case '{':
      return make_token(TokenKind::BraceLeft);
    case '}':
      return make_token(TokenKind::BraceRight);
    case '(':
      return make_token(TokenKind::ParenLeft);
    case ')':
      return make_token(TokenKind::ParenRight);
    case ';':
      return make_token(TokenKind::Semicolon);
    case '\0':
      return make_token(TokenKind::EndOfFile);
    case '-':
      if (char_at(0) == '>') {
        consume_char();
        return make_token(TokenKind::Arrow);
      } else {
        std::cerr << "unrecognized character '-'\n";
        std::exit(1);
      }
    default:
      if (std::isdigit(next)) {
        return make_number();
      } else if (is_ident_start(next)) {
        return make_identifier();
      } else {
        std::cerr << "unrecognized character '" << next << "'\n";
        std::exit(1);
      }
    }
  }

  std::vector<Token> Lexer::get_all_tokens() {
    std::vector<Token> tokens;
    while (true) {
      Token token = get_next_token();
      tokens.push_back(token);
      if (token.kind == TokenKind::EndOfFile) {
        return tokens;
      }
    }
  }

  Token Lexer::make_identifier() {
    while (is_ident(char_at(0))) {
      consume_char();
    }

    std::string lexeme = m_source.substr(m_start, m_pos - m_start);
    TokenKind kind = identifier_kind(lexeme);
    return make_token(kind);
  }

  Token Lexer::make_number() {
    while (std::isdigit(char_at(0))) {
      consume_char();
    }
    return make_token(TokenKind::Number);
  }

  Token Lexer::make_token(TokenKind kind) const {
    std::size_t lexeme_length = m_pos - m_start;
    return Token{
        .kind = kind,
        .lexeme = m_source.substr(m_start, lexeme_length),
        .line = m_line,
        .column = m_column - lexeme_length,
    };
  }

  void Lexer::skip_whitespace() {
    while (true) {
      if (char_at(0) == '\n') {
        consume_char();
        m_line++;
        m_column = 1;
      } else if (std::isspace(char_at(0))) {
        consume_char();
      } else if (char_at(0) == '/' && char_at(1) == '/') {
        while (char_at(0) != '\0' && char_at(0) != '\n') {
          consume_char();
        }
        if (char_at(0) == '\n') {
          consume_char();
          m_line++;
          m_column = 1;
        }
      } else {
        break;
      }
    }
  }

}
