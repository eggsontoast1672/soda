#pragma once

#include <exception>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include "soda/token.hpp"

namespace soda::lexer {

  using namespace token;

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
    /**
     * A pointer to the source code that was being tokenized when the error
     * occurred. We need this so we can print the erroneous line.
     */
    const char *m_source;

    // Location information
    std::filesystem::path m_file;
    std::size_t m_line;
    std::size_t m_column;

    /**
     * The error message to be printed when what() is called. We need to store
     * this here because what() has to return a const char *, which must be
     * valid for as long as the LexError object is.
     */
    std::string m_message;
  };

  class Lexer {
  public:
    explicit Lexer(const std::filesystem::path &file);

    std::optional<Token> next_token();

  private:
    std::filesystem::path m_file;
    std::size_t m_line = 1;
    std::size_t m_column = 1;

    std::string m_source;
    std::size_t m_start = 0;
    std::size_t m_position = 0;

    Token make_identifier();
    Token make_number();
    Token make_token(TokenKind kind) const;
    void skip_whitespace();
  };

  std::vector<Token> tokenize_source(std::string_view source);
  void print_lexer_error(const LexError &error);
}
