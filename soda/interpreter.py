import typing

import lexer
import parser
from util import SodaError

class Interpreter(parser.ExprVisitor):
    def evaluate(self, expr: parser.Expr) -> typing.Any:
        return expr.accept(self)

    def visit_binary_expr(self, expr: parser.BinaryExpr) -> typing.Any:
        left = self.evaluate(expr.left)
        right = self.evaluate(expr.right)
        match expr.operator.kind:
            case lexer.TokenKind.BANG_EQUAL:
                return left != right
            case lexer.TokenKind.EQUAL_EQUAL:
                return left == right
            case lexer.TokenKind.MINUS:
                if not isinstance(left, int) or not isinstance(right, int):
                    raise SodaError("arithmetic operators only supported for integers")
                return left - right
            case lexer.TokenKind.PLUS:
                if not isinstance(left, int) or not isinstance(right, int):
                    raise SodaError("arithmetic operators only supported for integers")
                return left + right
            case lexer.TokenKind.SLASH:
                if not isinstance(left, int) or not isinstance(right, int):
                    raise SodaError("arithmetic operators only supported for integers")
                return left // right
            case lexer.TokenKind.STAR:
                if not isinstance(left, int) or not isinstance(right, int):
                    raise SodaError("arithmetic operators only supported for integers")
                return left * right
            case _:
                assert False, "unreachable"

    def visit_unary_expr(self, expr: parser.UnaryExpr) -> typing.Any:
        operand = self.evaluate(expr.operand)
        match expr.operator.kind:
            case lexer.TokenKind.BANG:
                if not isinstance(operand, bool):
                    raise SodaError("unary bang only supported for booleans")
                else:
                    return not operand
            case lexer.TokenKind.MINUS:
                if not isinstance(operand, int):
                    raise SodaError("unary minus only supported for integers")
                else:
                    return -operand
            case _:
                assert False, "unreachable"

    def visit_literal_expr(self, expr: parser.LiteralExpr) -> typing.Any:
        return expr.value
