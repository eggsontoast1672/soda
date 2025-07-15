#include <filesystem>
#include <iostream>

#include "soda/fs.hpp"
#include "soda/lexer.hpp"
#include "soda/options.hpp"

#if 0

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

// Usage: soda [--tokens] [-o <file>] <file.soda>

static void print_files(const std::vector<std::string> &files) {
  std::cout << "{\n";
  for (const std::string &file : files) {
    std::cout << "  \"" << file << "\",\n";
  }
  std::cout << "}\n";
}

#endif

int main(int argc, char **argv) {
  using soda::options::Options;

  Options opts = soda::options::get(argc, argv);
  std::string contents = soda::fs::read_to_string(opts.files.at(0));
  soda::lexer::Lexer lexer{contents};
  std::vector<soda::token::Token> tokens = lexer.get_all_tokens();
  soda::token::dump_json(tokens, std::cout);
}
