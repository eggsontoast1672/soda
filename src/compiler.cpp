#include "soda/compiler.hpp"

#include <fstream>
#include <iostream>

#include "soda/parser.hpp"

namespace soda {
  void compile_file(std::filesystem::path input, std::filesystem::path output) {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit | std::ifstream::eofbit |
                    std::ifstream::failbit);
    file.open(input);
    std::ostringstream contents;
    contents << file.rdbuf();
    std::string source = contents.str();
    compile_source(source, output);
  }

  void compile_source(const std::string &source, std::filesystem::path path) {
    Program program = parse_source(source);
    compile_ast(program, path);
  }

  void compile_tokens(const std::vector<Token> &tokens,
                      std::filesystem::path path) {
    Program program = parse_tokens(tokens);
    compile_ast(program, path);
  }

  void compile_ast(Program program, std::filesystem::path path) {
    std::ofstream file{path};

    file << "global _start\n\n";
    file << "section .text\n";
    file << "_start:\n";
    file << "  mov rax, 0x3c\n";
    file << "  mov rdi, " << program << '\n';
    file << "  syscall\n";
  }

  void Compiler::visit_integer_literal(const IntegerLiteral &l) {}

  void Compiler::visit_return_statement(const ReturnStatement &s) {}
}
