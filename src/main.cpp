#include "soda/compiler.hpp"

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }
  soda::compile_file(argv[1], "output.asm");
}
