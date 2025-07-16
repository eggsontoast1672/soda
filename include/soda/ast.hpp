#ifndef SODA_AST_HPP
#define SODA_AST_HPP

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace soda {

class Statement;
class Expression;
class Type;

class ASTNode {
public:
  virtual ~ASTNode() = default;
};

class Statement : public ASTNode {
public:
  virtual ~Statement() = default;
};

class Expression : public ASTNode {
public:
  virtual ~Expression() = default;
};

class Declaration : public ASTNode {
public:
  virtual ~Declaration() = default;
};

class Type : public ASTNode {
public:
  virtual ~Type() = default;
};

class Identifier : public Expression {
public:
  explicit Identifier(std::string name) : m_name{std::move(name)} {}
  const char *get_name() const { return m_name.data(); }

private:
  std::string m_name;
};

class IntegerLiteral : public Expression {
public:
  explicit IntegerLiteral(std::int32_t value) : m_value{value} {}
  std::int32_t get_value() const { return m_value; }

private:
  std::int32_t m_value;
};

// Parameter declaration
class Parameter {
public:
  Parameter(std::string name, std::unique_ptr<Type> type)
      : m_name{std::move(name)}, m_type{std::move(type)} {}

  const char *get_name() const { return m_name.data(); }
  const Type *get_type() const { return m_type.get(); }

private:
  std::string m_name;
  std::shared_ptr<Type> m_type;
};

// Statements
class BlockStatement : public Statement {
public:
  explicit BlockStatement(std::vector<std::unique_ptr<Statement>> statements)
      : m_statements{std::move(statements)} {}
  const std::vector<std::unique_ptr<Statement>> &get_statements() const { return m_statements; }

private:
  std::vector<std::unique_ptr<Statement>> m_statements;
};

class ReturnStatement : public Statement {
public:
  explicit ReturnStatement(std::unique_ptr<Expression> expression)
      : m_return_value{std::move(expression)} {}
  const Expression *get_return_value() const { return m_return_value.get(); }

private:
  std::unique_ptr<Expression> m_return_value;
};

class FunctionDeclaration : public Declaration {
public:
  FunctionDeclaration(std::string name, std::optional<Type> returnType,
                      std::vector<Parameter> parameters, std::unique_ptr<BlockStatement> body)
      : m_name(std::move(name)), m_return_type(std::move(returnType)),
        m_parameters(std::move(parameters)), m_body(std::move(body)) {}

  const std::string &get_name() const { return m_name; }
  const std::optional<Type> &get_return_type() const { return m_return_type; }
  const std::vector<Parameter> &get_parameters() const { return m_parameters; }
  // const BlockStatement &get_body() const { return m_body; }

private:
  std::string m_name;
  std::optional<Type> m_return_type;
  std::vector<Parameter> m_parameters;
  std::unique_ptr<BlockStatement> m_body;
};

} // namespace soda

#endif
