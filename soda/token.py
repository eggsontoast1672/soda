from dataclasses import dataclass
from enum import Enum, auto
from typing import Any


class TokenKind(Enum):
    # One character tokens
    BRACE_LEFT = auto()
    BRACE_RIGHT = auto()
    COMMA = auto()
    DOT = auto()
    MINUS = auto()
    PAREN_LEFT = auto()
    PAREN_RIGHT = auto()
    PLUS = auto()
    SEMICOLON = auto()
    SLASH = auto()
    STAR = auto()

    # One or two character tokens
    AND_AND = auto()
    BANG = auto()
    BANG_EQUAL = auto()
    EQUAL = auto()
    EQUAL_EQUAL = auto()
    GREATER = auto()
    GREATER_EQUAL = auto()
    LESS = auto()
    LESS_EQUAL = auto()
    PIPE_PIPE = auto()

    # Many character tokens
    IDENTIFIER = auto()
    NUMBER = auto()
    STRING = auto()

    # Keywords
    ELSE = auto()
    FALSE = auto()
    FN = auto()
    FOR = auto()
    IF = auto()
    LET = auto()
    NULL = auto()
    PRINTLN = auto()
    RETURN = auto()
    SELF = auto()
    STRUCT = auto()
    SUPER = auto()
    TRUE = auto()
    WHILE = auto()

    # Other
    EOF = auto()


@dataclass
class Token:
    kind: TokenKind
    lexeme: str
    literal: Any
    line: int

    def __str__(self) -> str:
        return f"{self.kind} {self.lexeme} {self.literal}"


def identifier_kind(identifier: str) -> TokenKind:
    match identifier:
        case "else":
            return TokenKind.ELSE
        case "false":
            return TokenKind.FALSE
        case "fn":
            return TokenKind.FN
        case "for":
            return TokenKind.FOR
        case "if":
            return TokenKind.IF
        case "let":
            return TokenKind.LET
        case "null":
            return TokenKind.NULL
        case "println":
            return TokenKind.PRINTLN
        case "return":
            return TokenKind.RETURN
        case "self":
            return TokenKind.SELF
        case "struct":
            return TokenKind.STRUCT
        case "super":
            return TokenKind.SUPER
        case "true":
            return TokenKind.TRUE
        case "while":
            return TokenKind.WHILE
        case _:
            return TokenKind.IDENTIFIER