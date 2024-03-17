from typing import Any, Optional

from soda import token
from soda.token import Token, TokenKind


class Lexer:
    def __init__(self, source: str) -> None:
        self.source = source
        self.current = 0
        self.line = 1
        self.start = 0

    def advance(self) -> Optional[Token]:
        if self.current >= len(self.source):
            return None
        ch = self.source[self.current]
        self.current += 1
        return ch

    def next_token(self) -> Token:
        while (ch := self.peek()) is not None and ch.isspace():
            if ch == "\n":
                self.line += 1
            self.advance()
        self.start = self.current
        match self.advance():
            case "{":
                return self.make_token(TokenKind.BRACE_LEFT)
            case "}":
                return self.make_token(TokenKind.BRACE_RIGHT)
            case ",":
                return self.make_token(TokenKind.COMMA)
            case ".":
                return self.make_token(TokenKind.DOT)
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
            case "&":
                if self.match("&"):
                    return self.make_token(TokenKind.AND_AND)
                raise Exception("Unknown token '&'")
            case "!":
                if self.match("="):
                    return self.make_token(TokenKind.BANG_EQUAL)
                return self.make_token(TokenKind.BANG)
            case "=":
                if self.match("="):
                    return self.make_token(TokenKind.EQUAL_EQUAL)
                return self.make_token(TokenKind.EQUAL)
            case ">":
                if self.match("="):
                    return self.make_token(TokenKind.GREATER_EQUAL)
                return self.make_token(TokenKind.GREATER)
            case "<":
                if self.match("="):
                    return self.make_token(TokenKind.LESS_EQUAL)
                return self.make_token(TokenKind.LESS)
            case "|":
                if self.match("|"):
                    return self.make_token(TokenKind.PIPE_PIPE)
                raise Exception("Unknown token '|'")
            case '"':
                while self.advance() != '"':
                    pass
                return self.make_token(TokenKind.STRING)
            case None:
                return self.make_token(TokenKind.EOF)
            case ch if ch.isalpha() or ch == "_":
                while (ch := self.peek()) is not None and ch.isalnum():
                    self.advance()
                lexeme = self.source[self.start:self.current]
                kind = token.identifier_kind(lexeme)
                return Token(kind, lexeme, None, self.line)
            case ch if ch.isdigit():
                while (ch := self.peek()) is not None and ch.isdigit():
                    self.advance()
                lexeme = self.source[self.start:self.current]
                return Token(TokenKind.NUMBER, lexeme, int(lexeme), self.line)
            case ch:
                raise Exception(f"Unknown token '{ch}'")

    def make_token(self, kind: TokenKind, literal: Any = None) -> Token:
        lexeme = self.source[self.start:self.current]
        return Token(kind, lexeme, literal, self.line)

    def match(self, ch: str) -> bool:
        if self.source[self.current] == ch:
            self.current += 1
            return True
        return False
    
    def peek(self) -> Optional[str]:
        if self.current >= len(self.source):
            return None
        return self.source[self.current]


def tokenize(source: str) -> list[Token]:
    lexer = Lexer(source)
    tokens = []
    while (token := lexer.next_token()).kind != TokenKind.EOF:
        tokens.append(token)
    tokens.append(token)
    return tokens