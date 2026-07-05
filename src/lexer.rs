use std::{iter::Peekable, str::Chars};

#[derive(Clone, Copy, Debug)]
pub enum TokenKind {
    BraceLeft,
    BraceRight,
    ParenLeft,
    ParenRight,
    Semicolon,
    Arrow,
    Identifier,
    Number,
    Fn,
    Return,
    EndOfFile,
}

pub struct Token {
    kind: TokenKind,
    start: usize,
    end: usize,
}

impl TokenKind {
    pub fn from_ident(ident: &str) -> Self {
        match ident {
            "fn" => Self::Fn,
            "return" => Self::Return,
            _ => Self::Identifier,
        }
    }
}

struct Lexer<'a> {
    chars: Peekable<Chars<'a>>,
}

impl<'a> Lexer<'a> {
    pub fn next_token(&mut self) -> Token {
        let Some(next_char) = self.chars.next() else {
            return Token {
                kind: TokenKind::EndOfFile,
                start: 0,
                end: 0,
            };
        };

        match next_char {
            '{' => TokenKind::BraceLeft,
            '}' => TokenKind::BraceRight,
            '(' => TokenKind::ParenLeft,
            ')' => TokenKind::ParenRight,
            ';' => TokenKind::Semicolon,
            '-' => match self.chars.next() {
                Some('>') => TokenKind::Arrow,
                _ => panic!(),
            },
            _ => {
                if next_char.is_ascii_digit() {
                    while let Some(x) = self.chars.peek() {}
                }
            }
        }
    }
}
