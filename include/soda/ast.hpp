#ifndef SODA_AST_HPP
#define SODA_AST_HPP

#include <cstdint>
#include <memory>

namespace soda::ast {

  class Node {
  public:
    virtual ~Node() = default;
  };

  struct Expression : public Node {};

  class Identifier : public Expression {
  public:
    Identifier(const std::string &name)
      : m_name{name} {}

  private:
    std::string m_name;
  };

  class IntegerLiteral : public Expression {
  public:
    IntegerLiteral(std::int32_t value)
      : m_value{value} {}

  private:
    std::int32_t m_value;
  };

  class Statement : public Node {};

  class ReturnStatement : public Statement {
  public:
    ReturnStatement(std::unique_ptr<Expression> return_value)
      : m_return_value{std::move(return_value)} {}

  private:
    std::unique_ptr<Expression> m_return_value;
  };

  class Declaration : public Node {};

  struct FunctionParameter {
    Identifier name;
    Identifier type;
  };

  class FunctionDeclaration : public Declaration {
  public:
    FunctionDeclaration(Identifier name,
                        Identifier return_type,
                        std::vector<FunctionParameter> params,
                        std::vector<std::unique_ptr<Statement>> body)
      : m_name{name},
        m_return_type{return_type},
        m_params{params},
        m_body{std::move(body)} {}

  private:
    Identifier m_name;
    Identifier m_return_type;
    std::vector<FunctionParameter> m_params;
    std::vector<std::unique_ptr<Statement>> m_body;
  };

}

#endif
