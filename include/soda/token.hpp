#ifndef SODA_TOKEN_HPP
#define SODA_TOKEN_HPP

#include <string>
#include <vector>

namespace soda {

enum class TokenKind {
  BraceLeft,
  BraceRight,
  ParenLeft,
  ParenRight,
  Semicolon,
  Arrow,
  Identifier,
  Number,
  Fn,
  Return,
  EndOfFile,
};

std::ostream &operator<<(std::ostream &stream, TokenKind kind);
TokenKind identifier_kind(std::string_view lexeme);

struct Token {
  TokenKind kind;
  std::string lexeme;
  std::size_t line;
  std::size_t column;
};

void dump_tokens_to_json(const std::vector<Token> &tokens, std::ostream &stream);

} // namespace soda

#endif
