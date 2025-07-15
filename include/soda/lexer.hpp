#ifndef SODA_LEXER_HPP
#define SODA_LEXER_HPP

#include <string>

#include "soda/token.hpp"

namespace soda::lexer {

  class Lexer {
  public:
    explicit Lexer(const std::string &source);

    char char_at(std::size_t index);
    char consume_char();

    token::Token get_next_token();
    std::vector<token::Token> get_all_tokens();

  private:
    std::string m_source;
    std::size_t m_start = 0;
    std::size_t m_pos = 0;
    std::size_t m_line = 1;
    std::size_t m_column = 1;

    token::Token make_identifier();
    token::Token make_number();
    token::Token make_token(token::TokenKind kind) const;

    void skip_whitespace();
  };

}

#endif
