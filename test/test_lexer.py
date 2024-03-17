import unittest
from unittest import TestCase

from soda import lexer
from soda.token import Token, TokenKind


class LexerTestCase(TestCase):
    def test_arithmetic(self) -> None:
        source = """fn calculate(a, b) {
            while a != b && b == a * 8 - 1 / 9 {
                if a < 7 || b >= 90 {
                    a = a + b;
                }
            }
            return a / b * 2;
        }"""
        expected = [
            # Line 1
            Token(TokenKind.FN, "fn", None, 1),
            Token(TokenKind.IDENTIFIER, "calculate", None, 1),
            Token(TokenKind.PAREN_LEFT, "(", None, 1),
            Token(TokenKind.IDENTIFIER, "a", None, 1),
            Token(TokenKind.COMMA, ",", None, 1),
            Token(TokenKind.IDENTIFIER, "b", None, 1),
            Token(TokenKind.PAREN_RIGHT, ")", None, 1),
            Token(TokenKind.BRACE_LEFT, "{", None, 1),

            # Line 2
            Token(TokenKind.WHILE, "while", None, 2),
            Token(TokenKind.IDENTIFIER, "a", None, 2),
            Token(TokenKind.BANG_EQUAL, "!=", None, 2),
            Token(TokenKind.IDENTIFIER, "b", None, 2),
            Token(TokenKind.AND_AND, "&&", None, 2),
            Token(TokenKind.IDENTIFIER, "b", None, 2),
            Token(TokenKind.EQUAL_EQUAL, "==", None, 2),
            Token(TokenKind.IDENTIFIER, "a", None, 2),
            Token(TokenKind.STAR, "*", None, 2),
            Token(TokenKind.NUMBER, "8", 8, 2),
            Token(TokenKind.MINUS, "-", None, 2),
            Token(TokenKind.NUMBER, "1", 1, 2),
            Token(TokenKind.SLASH, "/", None, 2),
            Token(TokenKind.NUMBER, "9", 9, 2),
            Token(TokenKind.BRACE_LEFT, "{", None, 2),

            # Line 3
            Token(TokenKind.IF, "if", None, 3),
            Token(TokenKind.IDENTIFIER, "a", None, 3),
            Token(TokenKind.LESS, "<", None, 3),
            Token(TokenKind.NUMBER, "7", 7, 3),
            Token(TokenKind.PIPE_PIPE, "||", None, 3),
            Token(TokenKind.IDENTIFIER, "b", None, 3),
            Token(TokenKind.GREATER_EQUAL, ">=", None, 3),
            Token(TokenKind.NUMBER, "90", 90, 3),
            Token(TokenKind.BRACE_LEFT, "{", None, 3),

            # Line 4
            Token(TokenKind.IDENTIFIER, "a", None, 4),
            Token(TokenKind.EQUAL, "=", None, 4),
            Token(TokenKind.IDENTIFIER, "a", None, 4),
            Token(TokenKind.PLUS, "+", None, 4),
            Token(TokenKind.IDENTIFIER, "b", None, 4),
            Token(TokenKind.SEMICOLON, ";", None, 4),

            # Line 5
            Token(TokenKind.BRACE_RIGHT, "}", None, 5),

            # Line 6
            Token(TokenKind.BRACE_RIGHT, "}", None, 6),

            # Line 7
            Token(TokenKind.RETURN, "return", None, 7),
            Token(TokenKind.IDENTIFIER, "a", None, 7),
            Token(TokenKind.SLASH, "/", None, 7),
            Token(TokenKind.IDENTIFIER, "b", None, 7),
            Token(TokenKind.STAR, "*", None, 7),
            Token(TokenKind.NUMBER, "2", 2, 7),
            Token(TokenKind.SEMICOLON, ";", None, 7),

            # Line 8
            Token(TokenKind.BRACE_RIGHT, "}", None, 8),
            Token(TokenKind.EOF, "", None, 8)
        ]
        recieved = lexer.tokenize(source)
        self.assertEqual(expected, recieved)

    def test_function(self) -> None:
        source = """fn main(args) {
            return 0;
        }"""
        expected = [
            # Line 1
            Token(TokenKind.FN, "fn", None, 1),
            Token(TokenKind.IDENTIFIER, "main", None, 1),
            Token(TokenKind.PAREN_LEFT, "(", None, 1),
            Token(TokenKind.IDENTIFIER, "args", None, 1),
            Token(TokenKind.PAREN_RIGHT, ")", None, 1),
            Token(TokenKind.BRACE_LEFT, "{", None, 1),

            # Line 2
            Token(TokenKind.RETURN, "return", None, 2),
            Token(TokenKind.NUMBER, "0", 0, 2),
            Token(TokenKind.SEMICOLON, ";", None, 2),

            # Line 3
            Token(TokenKind.BRACE_RIGHT, "}", None, 3),
            Token(TokenKind.EOF, "", None, 3)
        ]
        recieved = lexer.tokenize(source)
        self.assertEqual(expected, recieved)


if __name__ == "__main__":
    unittest.main()