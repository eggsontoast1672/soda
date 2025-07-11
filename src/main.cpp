#include <filesystem>
#include <iostream>

#include "soda/compiler.hpp"

static void format_lexer_error() {
  // We need a pointer to the source code, or at least to the line on which the
  // error resides.
  const char *const source = "fn maim() { return 0; }";

  // We also need information about where in the source code the error is, so we
  // can print it out nicely.
  const char *const error_file = "/home/paul/source/soda/src/main.cpp";
  const int error_line = 1;
  const int error_column = 4;
  const int error_length = 4;

  std::cerr << error_file << ':' << error_line << ':' << error_column
            << ": error: expected function to be called main\n";
  std::cerr << std::setw(5) << error_line << " | " << source << '\n';
  std::cerr << "      | ";
  for (int i = 0; i < error_column - 1; i++) {
    std::cerr << ' ';
  }
  std::cerr << '^';
  for (int i = 0; i < error_length - 1; i++) {
    std::cerr << '~';
  }
  std::cerr << '\n';
}

int main(int argc, const char *argv[]) {
  format_lexer_error();
  return 0;

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file>\n";
    return 1;
  }
  soda::compile_file(argv[1], "output.asm");
}
