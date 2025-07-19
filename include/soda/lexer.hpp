#ifndef SODA_LEXER_HPP
#define SODA_LEXER_HPP

#include <string>

#include "soda/token.hpp"

namespace soda {

std::vector<Token> tokenize(const std::string &source);

}

#endif
