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
