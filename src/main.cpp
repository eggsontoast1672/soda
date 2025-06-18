#include "soda/compiler.hpp"
#include "soda/lexer.hpp"
#include "soda/parser.hpp"

int main() {
  std::string source = "fn main() { return 65; }";
  std::vector<soda::Token> tokens = soda::tokenize(source);
  soda::Program program = soda::parse_tokens(tokens);
  soda::compile_program(program, "out.asm");
}
