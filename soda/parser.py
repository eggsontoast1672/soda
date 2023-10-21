from __future__ import annotations

import abc
import dataclasses
import typing

from . import lexer
from .util import SodaError


class Expr(abc.ABC):
    @abc.abstractmethod
    def accept(self, visitor: ExprVisitor) -> typing.Any:
        pass


@dataclasses.dataclass
class BinaryExpr(Expr):
    left: Expr
    right: Expr
    operator: lexer.Token
    
    def accept(self, visitor: ExprVisitor) -> typing.Any:
        return visitor.visit_binary_expr(self)


@dataclasses.dataclass
class UnaryExpr(Expr):
    operand: Expr
    operator: lexer.Token

    def accept(self, visitor: ExprVisitor) -> typing.Any:
        return visitor.visit_unary_expr(self)


@dataclasses.dataclass
class LiteralExpr(Expr):
    value: typing.Any

    def accept(self, visitor) -> typing.Any:
        return visitor.visit_literal_expr(self)


class ExprVisitor(abc.ABC):
    @abc.abstractmethod
    def visit_binary_expr(self, expr: BinaryExpr) -> typing.Any:
        pass

    @abc.abstractmethod
    def visit_unary_expr(self, expr: UnaryExpr) -> typing.Any:
        pass

    @abc.abstractmethod
    def visit_literal_expr(self, expr: LiteralExpr) -> typing.Any:
        pass


class Parser:
    def __init__(self, tokens: list[lexer.Token]) -> None:
        self.tokens = tokens
        self.current = 0

    def consume(self, kind: lexer.TokenKind) -> None:
        if self.tokens[self.current].kind != kind:
            raise SodaError(f"expected {kind} near {self.tokens[self.current].kind}")
        self.current += 1

    def get_next_expr(self) -> Expr:
        try:
            return self.get_next_comparison()
        except IndexError:
            raise SodaError("reached end of expression prematurely")

    def get_next_comparison(self) -> Expr:
        left = self.get_next_term()
        while self.has_tokens() and self.tokens[self.current].kind in (
            lexer.TokenKind.BANG_EQUAL,
            lexer.TokenKind.EQUAL_EQUAL
        ):
            operator = self.tokens[self.current]
            self.current += 1
            left = BinaryExpr(left, self.get_next_term(), operator)
        return left

    def get_next_term(self) -> Expr:
        left = self.get_next_factor()
        while self.has_tokens() and self.tokens[self.current].kind in (lexer.TokenKind.MINUS, lexer.TokenKind.PLUS):
            operator = self.tokens[self.current]
            self.current += 1
            left = BinaryExpr(left, self.get_next_factor(), operator)
        return left

    def get_next_factor(self) -> Expr:
        left = self.get_next_unary()
        while self.has_tokens() and self.tokens[self.current].kind in (lexer.TokenKind.SLASH, lexer.TokenKind.STAR):
            operator = self.tokens[self.current]
            self.current += 1
            left = BinaryExpr(left, self.get_next_unary(), operator)
        return left

    def get_next_unary(self) -> Expr:
        # One element tuple so it is easier to add stuff later
        if self.tokens[self.current].kind in (lexer.TokenKind.BANG, lexer.TokenKind.MINUS):
            operator = self.tokens[self.current]
            self.current += 1
            return UnaryExpr(self.get_next_unary(), operator)
        else:
            return self.get_next_atom()

    def get_next_atom(self) -> Expr:
        match self.tokens[self.current].kind:
            case lexer.TokenKind.FALSE:
                expr = LiteralExpr(False)
                self.current += 1
                return expr
            case lexer.TokenKind.TRUE:
                expr = LiteralExpr(True)
                self.current += 1
                return expr
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
                raise SodaError("expected number")

    def has_tokens(self) -> bool:
        return self.current < len(self.tokens)


def parse(tokens: list[lexer.Token]) -> Expr:
    return Parser(tokens).get_next_expr()
