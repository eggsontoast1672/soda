from __future__ import annotations

import abc
import dataclasses

import lexer


class Expr(abc.ABC):
    @abc.abstractmethod
    def accept(self, visitor: ExprVisitor) -> int:
        pass


@dataclasses.dataclass
class BinaryExpr(Expr):
    left: Expr
    right: Expr
    operator: lexer.Token
    
    def accept(self, visitor: ExprVisitor) -> int:
        return visitor.visit_binary_expr(self)


@dataclasses.dataclass
class LiteralExpr(Expr):
    value: int

    def accept(self, visitor) -> int:
        return visitor.visit_literal_expr(self)


class ExprVisitor(abc.ABC):
    @abc.abstractmethod
    def visit_binary_expr(self, expr: BinaryExpr) -> int:
        pass

    @abc.abstractmethod
    def visit_literal_expr(self, expr: LiteralExpr) -> int:
        pass


class ParseError(Exception):
    def __init__(self, message: str) -> None:
        super().__init__()
        self.message = message

    def __str__(self) -> str:
        return self.message


class Parser:
    def __init__(self, tokens: list[lexer.Token]) -> None:
        self.tokens = tokens
        self.current = 0

    def consume(self, kind: lexer.TokenKind) -> None:
        if self.tokens[self.current].kind != kind:
            raise ParseError(f"expected {kind} near {self.tokens[self.current].kind}")
        self.current += 1

    def get_next_expr(self) -> Expr:
        try:
            return self.get_next_term()
        except IndexError:
            raise ParseError("reached end of expression prematurely")

    def get_next_term(self) -> Expr:
        left = self.get_next_factor()
        while self.has_tokens() and self.tokens[self.current].kind in (lexer.TokenKind.MINUS, lexer.TokenKind.PLUS):
            operator = self.tokens[self.current]
            self.current += 1
            left = BinaryExpr(left, self.get_next_factor(), operator)
        return left

    def get_next_factor(self) -> Expr:
        left = self.get_next_atom()
        while self.has_tokens() and self.tokens[self.current].kind in (lexer.TokenKind.SLASH, lexer.TokenKind.STAR):
            operator = self.tokens[self.current]
            self.current += 1
            left = BinaryExpr(left, self.get_next_atom(), operator)
        return left

    def get_next_atom(self) -> Expr:
        match self.tokens[self.current].kind:
            case lexer.TokenKind.NUMBER:
                expr = LiteralExpr(int(self.tokens[self.current].lexeme))
                self.current += 1
                return expr
            case lexer.TokenKind.PAREN_LEFT:
                self.current += 1
                expr = self.get_next_expr()
                self.consume(lexer.TokenKind.PAREN_RIGHT)
                return expr
            case _:
                raise ParseError("expected number")

    def has_tokens(self) -> bool:
        return self.current < len(self.tokens)


def parse(tokens: list[lexer.Token]) -> Expr:
    return Parser(tokens).get_next_expr()
