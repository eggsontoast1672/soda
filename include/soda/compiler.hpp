#pragma once

#include <filesystem>
#include <vector>

#include "soda/ast.hpp"
#include "soda/token.hpp"

namespace soda {
  /**
   * Compile a soda file to assembly.
   *
   * The file supplied as `input` is read into a string, which is subsequently
   * compiled to assembly and written to the file supplied as `output`. Any I/O
   * errors that occur while reading or writing are thrown as exceptions.
   *
   * @param input The file containing the source to be read.
   * @param output The file to which the assembly is to be written.
   */
  void compile_file(std::filesystem::path input, std::filesystem::path output);

  /**
   * Compile soda source code to assembly.
   *
   * @param source The source to be compiled.
   * @param path The path of the file to which the assembly should be written.
   */
  void compile_source(const std::string &source, std::filesystem::path path);

  /**
   * Compile a list of tokens to assembly.
   *
   * @param tokens The token stream to be compiled.
   * @param path The path of the file to which the assembly should be written.
   */
  void compile_tokens(const std::vector<Token> &tokens,
                      std::filesystem::path path);

  /**
   * Compile a program AST to assembly.
   *
   * @param program The syntax tree to be compiled.
   * @param path The path of the file to which the assembly should be written.
   */
  void compile_ast(Program program, std::filesystem::path path);

  class Compiler : public ASTVisitor {
  public:
    void visit_integer_literal(const IntegerLiteral &l) override;
    void visit_return_statement(const ReturnStatement &s) override;
  };
}
