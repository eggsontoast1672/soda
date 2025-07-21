#ifndef SODA_OPTIONS_HPP
#define SODA_OPTIONS_HPP

#include <filesystem>
#include <optional>
#include <vector>

namespace soda {

  struct Options {
    bool dump_tokens = false;
    std::optional<std::filesystem::path> output_path;
    std::vector<std::string> files;
  };

  Options parse_options(int argc, char **argv);

}

#endif
