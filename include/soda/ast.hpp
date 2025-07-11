#pragma once

#include <memory>

namespace soda {
  using Program = int;

  class ASTVisitor;

  class Node {
  public:
    virtual void accept(ASTVisitor &visitor) = 0;
  };

  struct Expression : public Node {};

  struct IntegerLiteral;

  struct Statement : public Node {};

  struct ReturnStatement;

  class ASTVisitor {
  public:
    virtual void visit_integer_literal(const IntegerLiteral &l) = 0;
    virtual void visit_return_statement(const ReturnStatement &s) = 0;
  };

  struct IntegerLiteral : public Expression {
    int value;

    inline void accept(ASTVisitor &visitor) override {
      visitor.visit_integer_literal(*this);
    }
  };

  struct ReturnStatement : public Statement {
    std::unique_ptr<Expression> expression;

    inline void accept(ASTVisitor &visitor) override {
      visitor.visit_return_statement(*this);
    }
  };
}
