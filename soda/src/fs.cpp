#include <filesystem>
#include <fstream>
#include <iostream>

namespace soda {

  std::string read_path_to_string(const std::filesystem::path &path) {
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
