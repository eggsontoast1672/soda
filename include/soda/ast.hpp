#ifndef SODA_AST_HPP
#define SODA_AST_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace soda {

/////////////////
// Expressions //
/////////////////

struct Identifier {
  std::string name;
};

struct IntegerLiteral {
  std::int32_t value;
};

using Expression = std::variant<Identifier, IntegerLiteral>;

////////////////
// Statements //
////////////////

struct BlockStatement;
struct ReturnStatement;

using Statement = std::variant<BlockStatement, ReturnStatement>;

struct BlockStatement {
  std::vector<Statement> statements;
};

struct ReturnStatement {
  Expression return_value;
};

//////////////////
// Declarations //
//////////////////

struct TypedIdentifier {
  std::string name;
  std::string type;
};

struct FunctionDeclaration {
  std::string name;
  std::optional<std::string> return_type;
  std::vector<TypedIdentifier> params;
  BlockStatement body;
};

using Declaration = std::variant<FunctionDeclaration>;

} // namespace soda

#endif
