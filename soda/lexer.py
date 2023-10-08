import dataclasses
import enum
import typing


class TokenKind(enum.Enum):
    # Single character tokens
    MINUS = enum.auto()
    PLUS = enum.auto()
    SLASH = enum.auto()
    STAR = enum.auto()

    # Arbitrary length tokens
    NUMBER = enum.auto()


@dataclasses.dataclass
class Token:
    kind: TokenKind
    lexeme: str


class LexError(Exception):
    def __init__(self, char: str) -> None:
        super().__init__()
        self.char = char
    
    def __str__(self) -> str:
        return f"Unexpected character '{self.char}'"


class Lexer:
    def __init__(self, source: str) -> None:
        self.source = source
        self.current = 0
        self.start = 0

    def __iter__(self) -> typing.Self:
        return self

    def __next__(self) -> Token:
        try:
            return self.get_next_token()
        except IndexError:
            raise StopIteration

    def get_next_token(self) -> Token:
        self.start = self.current
        if self.source[self.current] == "-":
            self.current += 1
            return self.make_token(TokenKind.MINUS)
        elif self.source[self.current] == "+":
            self.current += 1
            return self.make_token(TokenKind.PLUS)
        elif self.source[self.current] == "/":
            self.current += 1
            return self.make_token(TokenKind.SLASH)
        elif self.source[self.current] == "*":
            self.current += 1
            return self.make_token(TokenKind.STAR)
        elif self.source[self.current].isdigit():
            self.current += 1
            # If there's an index error, we have to catch it because we need to
            # ensure that we get to the return statement. If that doesn't
            # happen, the last number token in the source code will be ignored.
            try:
                while self.source[self.current].isdigit():
                    self.current += 1
            except IndexError:
                pass
            return self.make_token(TokenKind.NUMBER)
        elif self.source[self.current].isspace():
            self.current += 1
            while self.source[self.current].isspace():
                self.current += 1
            # I'm having mixed feelings about making this function recursive,
            # but let's go for it for now and see what happens.
            return next(self)
        else:
            raise LexError(self.source[self.current])

    def make_token(self, kind: TokenKind) -> Token:
        return Token(kind, self.source[self.start:self.current])


def tokenize(source: str) -> typing.Iterable[Token]:
    yield from Lexer(source)
