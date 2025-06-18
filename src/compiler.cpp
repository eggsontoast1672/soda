#include "soda/compiler.hpp"

#include <fstream>

namespace soda {

void compile_program(Program program, std::filesystem::path path) {
  std::ofstream file{path};

  file << "global _start\n\n";
  file << "section .text\n";
  file << "_start:\n";
  file << "  mov rax, 0x3c\n";
  file << "  mov rdi, " << program << '\n';
  file << "  syscall\n";
}

} // namespace soda
