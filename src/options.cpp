#include "soda/options.hpp"

#include <cstring>
#include <iostream>

static void print_usage_and_exit(const char *program) {
  std::cerr << "Usage: " << program << " [OPTIONS] INPUT\n\n";
  std::cerr << "Options:\n";
  std::cerr << "    -o <FILENAME>       Write output to FILENAME\n";
  std::cerr << "    --tokens            Dump the tokens of a file\n";
  std::exit(1);
}

namespace soda {

  Options parse_options(int argc, char **argv) {
    Options options;

    for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i], "--tokens") == 0) {
        options.dump_tokens = true;
      } else if (std::strcmp(argv[i], "-o") == 0) {
        i++;
        if (i < argc) {
          options.output_path = argv[i];
        } else {
          print_usage_and_exit(argv[0]);
        }
      } else {
        options.files.push_back(argv[i]);
      }
    }

    if (options.files.empty()) {
      print_usage_and_exit(argv[0]);
    }

    return options;
  }

}
