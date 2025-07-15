#ifndef SODA_OPTIONS_HPP
#define SODA_OPTIONS_HPP

#include <filesystem>
#include <optional>
#include <vector>

namespace soda::options {

  struct Options {
    bool dump_tokens = false;
    std::optional<std::filesystem::path> output_path;
    std::vector<std::string> files;
  };
  
  void print_usage_and_exit(const char *program);
  Options get(int argc, char **argv);

}

#endif
