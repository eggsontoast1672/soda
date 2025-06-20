#pragma once

#include <exception>
#include <string>
#include <vector>

#include "soda/token.hpp"

namespace soda {

/**
 * An error which occurs during lexing, representing the presence of an
 * unrecognized character.
 */
class LexError : public std::exception {
public:
  explicit LexError(const char *source, std::size_t line, std::size_t column);

  /**
   * A formatted error message from the lexer.
   */
  inline const char *what() const noexcept override {
    return m_message.c_str();
  }

private:
  const char *m_source;
  std::size_t m_line;
  std::size_t m_column;

  std::string m_message;
};

class Lexer {
public:
  explicit Lexer(std::string_view source);

  void skip_whitespace();
  Token next_token();

private:
  std::string::const_iterator m_it;
  std::string::const_iterator m_end;
};

std::vector<Token> tokenize_source(std::string_view source);
void print_lexer_error(const LexError &error);

} // namespace soda
