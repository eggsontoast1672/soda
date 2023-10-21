import dataclasses
import typing
from enum import Enum, auto

from .util import SodaError


class TokenKind(Enum):
    # One character tokens
    BANG = auto()
    BRACE_LEFT = auto()
    BRACE_RIGHT = auto()
    EQUAL = auto()
    MINUS = auto()
    PAREN_LEFT = auto()
    PAREN_RIGHT = auto()
    PLUS = auto()
    SEMICOLON = auto()
    SLASH = auto()
    STAR = auto()

    # Two character tokens
    BANG_EQUAL = auto()
    EQUAL_EQUAL = auto()

    # Many character tokens
    FALSE = auto()
    TRUE = auto()
    FN = auto()
    IDENTIFIER = auto()
    NUMBER = auto()
    RETURN = auto()

    # Other
    UNKNOWN = auto()
    EOF = auto()


@dataclasses.dataclass
class Token:
    kind: TokenKind
    lexeme: str


class Lexer:
    def __init__(self, source: str) -> None:
        self.source = source
        self.current = 0
        self.start = 0

    def get_next_token(self) -> Token:
        self.start = self.current
        if not self.has_next_token():
            return self.make_token(TokenKind.EOF)
        match self.next_char():
            case "{":
                return self.make_token(TokenKind.BRACE_LEFT)
            case "}":
                return self.make_token(TokenKind.BRACE_RIGHT)
            case "!":
                if self.next_if_equal("="):
                    return self.make_token(TokenKind.BANG_EQUAL)
                return self.make_token(TokenKind.BANG)
            case "=":
                if self.next_if_equal("="):
                    return self.make_token(TokenKind.EQUAL_EQUAL)
                return self.make_token(TokenKind.EQUAL)
            case "-":
                return self.make_token(TokenKind.MINUS)
            case "(":
                return self.make_token(TokenKind.PAREN_LEFT)
            case ")":
                return self.make_token(TokenKind.PAREN_RIGHT)
            case "+":
                return self.make_token(TokenKind.PLUS)
            case ";":
                return self.make_token(TokenKind.SEMICOLON)
            case "/":
                return self.make_token(TokenKind.SLASH)
            case "*":
                return self.make_token(TokenKind.STAR)
            case c:
                return self.next_multi_char_token(c)

    def next_if_equal(self, c: str) -> bool:
        if self.has_next_token() and self.source[self.current] == c:
            self.get_next_token()
            return True
        else:
            return False

    def next_char(self) -> str:
        c = self.source[self.current]
        self.current += 1
        return c

    def next_number(self) -> Token:
        while self.has_next_token():
            c = self.next_char()
            if not c.isdigit():
                break
        return self.make_token(TokenKind.NUMBER)
    
    def next_keyword_or_ident(self) -> Token:
        while self.has_next_token():
            c = self.next_char()
            if not c.isalnum():
                break
        match self.source[self.start:self.current]:
            case "false":
                return self.make_token(TokenKind.FALSE)
            case "fn":
                return self.make_token(TokenKind.FN)
            case "return":
                return self.make_token(TokenKind.RETURN)
            case "true":
                return self.make_token(TokenKind.TRUE)
            case _:
                return self.make_token(TokenKind.IDENTIFIER)

    def next_multi_char_token(self, first: str) -> Token:
        if first.isdigit():
            return self.next_number()
        elif first.isalpha():
            return self.next_keyword_or_ident()
        else:
            return self.make_token(TokenKind.UNKNOWN)

    def make_token(self, kind: TokenKind) -> Token:
        return Token(kind, self.source[self.start:self.current])

    def has_next_token(self) -> bool:
        return self.current < len(self.source)


def tokenize(source: str) -> typing.Iterable[Token]:
    yield from Lexer(source)
