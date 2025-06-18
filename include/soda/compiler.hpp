#pragma once

#include <filesystem>

#include "soda/ast.hpp"

namespace soda {

void compile_program(Program program, std::filesystem::path path);

}
