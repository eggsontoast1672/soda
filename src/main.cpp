#include <filesystem>
#include <fstream>
#include <iostream>

#include "soda/fs.hpp"
#include "soda/lexer.hpp"
#include "soda/options.hpp"

int main(int argc, char **argv) {
  soda::Options opts = soda::parse_options(argc, argv);
  if (!opts.dump_tokens) {
    std::cerr << "This part of the compiler is not yet implemented.\n";
    std::cerr << "Please add the '--tokens' option.\n";
    std::exit(1);
  }

  std::string contents = soda::read_path_to_string(opts.files.at(0));
  std::vector<soda::Token> tokens = soda::tokenize(contents);

  if (opts.output_path) {
    std::ofstream stream{*opts.output_path};
    soda::dump_tokens_to_json(tokens, stream);
  } else {
    soda::dump_tokens_to_json(tokens, std::cout);
  }
}

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

#endif
