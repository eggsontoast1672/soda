#include "soda/token.hpp"

namespace soda {
  TokenKind identifier_kind(std::string_view lexeme) {
    if (lexeme == "fn") {
      return TokenKind::Fn;
    } else if (lexeme == "return") {
      return TokenKind::Return;
    } else {
      return TokenKind::Identifier;
    }
  }
}
