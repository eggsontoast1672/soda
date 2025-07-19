%{

#include <iostream>

#include "soda/token.hpp"

using namespace soda;

static std::vector<Token> s_tokens;

#define MAKE_TOKEN(kind) Token{kind, yytext, 0, 0}

extern "C" int yywrap() {
  s_tokens.push_back(MAKE_TOKEN(TokenKind::EndOfFile));
  return 1;
}

%}

IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*
INTEGER     [0-9]+

%%

"{"   s_tokens.push_back(MAKE_TOKEN(TokenKind::BraceLeft));
"}"   s_tokens.push_back(MAKE_TOKEN(TokenKind::BraceRight));
"("   s_tokens.push_back(MAKE_TOKEN(TokenKind::ParenLeft));
")"   s_tokens.push_back(MAKE_TOKEN(TokenKind::ParenRight));
";"   s_tokens.push_back(MAKE_TOKEN(TokenKind::Semicolon));
"->"  s_tokens.push_back(MAKE_TOKEN(TokenKind::Arrow));

fn      s_tokens.push_back(MAKE_TOKEN(TokenKind::Fn));
return  s_tokens.push_back(MAKE_TOKEN(TokenKind::Return));

{IDENTIFIER}  s_tokens.push_back(MAKE_TOKEN(TokenKind::Identifier));
{INTEGER}     s_tokens.push_back(MAKE_TOKEN(TokenKind::Number));

"//"[^\n]*  /* Eat single-line comments */
[ \t\n]+    /* Eat white space */

. {
    std::cerr << "Unrecognized token: '" << yytext << "'\n";
    std::exit(1);
  }

%%

namespace soda {

std::vector<Token> tokenize(const std::string &source) {
  s_tokens.clear();
  YY_BUFFER_STATE buffer = yy_scan_string(source.c_str());
  yylex();
  yy_delete_buffer(buffer);
  return s_tokens;
}

} // namespace soda
