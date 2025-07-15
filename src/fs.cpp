#include "soda/fs.hpp"

#include <fstream>
#include <iostream>

namespace soda::fs {

  std::string read_to_string(const std::filesystem::path &path) {
    std::ifstream file{path};
    if (!file.is_open()) {
      std::cerr << "failed to open file " << path << '\n';
      std::exit(1);
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
  }

}
