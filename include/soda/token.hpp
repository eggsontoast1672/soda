#pragma once

#include <string>

namespace soda {

enum class TokenKind {
  BraceLeft,
  BraceRight,
  ParenLeft,
  ParenRight,
  Semicolon,
  Identifier,
  Number,
  Fn,
  Return,
  EndOfFile,
};

TokenKind identifier_kind(std::string_view lexeme);

struct Token {
  TokenKind kind;
  std::string lexeme;
};

} // namespace soda
