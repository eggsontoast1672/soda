#include "soda/token.hpp"

#include <iostream>

namespace soda::token {

  std::ostream &operator<<(std::ostream &stream, TokenKind kind) {
    stream << "TokenKind::";

    switch (kind) {
    case TokenKind::BraceLeft:
      stream << "BraceLeft";
      break;
    case TokenKind::BraceRight:
      stream << "BraceRight";
      break;
    case TokenKind::ParenLeft:
      stream << "ParenLeft";
      break;
    case TokenKind::ParenRight:
      stream << "ParenRight";
      break;
    case TokenKind::Semicolon:
      stream << "Semicolon";
      break;
    case TokenKind::Arrow:
      stream << "Arrow";
      break;
    case TokenKind::Identifier:
      stream << "Identifier";
      break;
    case TokenKind::Number:
      stream << "Number";
      break;
    case TokenKind::Fn:
      stream << "Fn";
      break;
    case TokenKind::Return:
      stream << "Return";
      break;
    case TokenKind::EndOfFile:
      stream << "EndOfFile";
      break;
    }

    return stream;
  }

  TokenKind identifier_kind(std::string_view lexeme) {
    if (lexeme == "fn") {
      return TokenKind::Fn;
    } else if (lexeme == "return") {
      return TokenKind::Return;
    } else {
      return TokenKind::Identifier;
    }
  }

  void dump_json(const std::vector<Token> &tokens, std::ostream &stream) {
    stream << "[\n";
    for (std::size_t i = 0; i < tokens.size(); i++) {
      stream << "  { \"kind\": \"" << tokens[i].kind << "\",";
      stream << " \"lexeme\": \"" << tokens[i].lexeme << "\",";
      stream << " \"line\": " << tokens[i].line << ',';
      stream << " \"column\": " << tokens[i].column << " }";
      if (i < tokens.size() - 1) {
        stream << ',';
      }
      stream << '\n';
    }
    stream << "]\n";
  }

}
