#ifndef SODA_FS_HPP
#define SODA_FS_HPP

#include <filesystem>
#include <string>

namespace soda {

  std::string read_path_to_string(const std::filesystem::path &path);

}

#endif
