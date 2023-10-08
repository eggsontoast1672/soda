import lexer
import parser

class Interpreter(parser.ExprVisitor):
    def evaluate(self, expr: parser.Expr) -> int:
        return expr.accept(self)

    def visit_binary_expr(self, expr: parser.BinaryExpr) -> int:
        left = self.evaluate(expr.left)
        right = self.evaluate(expr.right)
        match expr.operator.kind:
            case lexer.TokenKind.MINUS:
                return left - right
            case lexer.TokenKind.PLUS:
                return left + right
            case lexer.TokenKind.SLASH:
                return left // right
            case lexer.TokenKind.STAR:
                return left * right
        assert False, "unreachable"

    def visit_literal_expr(self, expr: parser.LiteralExpr) -> int:
        return expr.value
