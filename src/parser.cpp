#include "soda/parser.hpp"

#include "soda/lexer.hpp"

namespace soda {
  ParseError::ParseError(const std::string &what_arg)
      : std::runtime_error{what_arg} {}

  Parser::Parser(const std::vector<Token> &tokens) : m_tokens{tokens} {}

  Token Parser::consume(TokenKind expected, const std::string &message) {
    if (m_pos < m_tokens.size() && m_tokens[m_pos].kind == expected) {
      Token token = m_tokens[m_pos];
      m_pos += 1;
      return token;
    } else {
      throw ParseError{message};
    }
  }

  Program Parser::program() {
    consume(TokenKind::Fn, "expected 'fn' keyword");
    Token identifier = consume(TokenKind::Identifier, "expected identifier");
    if (identifier.lexeme != "main") {
      throw ParseError{"expected function to be called 'main'"};
    }
    consume(TokenKind::ParenLeft, "expected '('");
    consume(TokenKind::ParenRight, "expected ')'");
    consume(TokenKind::BraceLeft, "expected '{'");
    consume(TokenKind::Return, "expected 'return'");
    Token number = consume(TokenKind::Number, "expected number");
    int return_value = std::stoi(number.lexeme);
    consume(TokenKind::Semicolon, "expected ';'");
    consume(TokenKind::BraceRight, "expected '}'");
    if (m_pos < m_tokens.size()) {
      throw ParseError{"expected end of file"};
    }
    return return_value;
  }

  Program parse_source(std::string_view source) {
    std::vector<Token> tokens = tokenize_source(source);
    return parse_tokens(tokens);
  }

  Program parse_tokens(const std::vector<Token> &tokens) {
    Parser parser{tokens};
    return parser.program();
  }
}
