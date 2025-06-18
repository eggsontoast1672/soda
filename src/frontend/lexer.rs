use std::{iter::Peekable, result, str::Chars};

use crate::frontend::token::{Token, TokenKind};

#[derive(Debug)]
pub struct Error {
    pub character: char,
}

impl Error {
    pub const fn new(character: char) -> Self {
        Self { character }
    }
}

pub type Result<T> = result::Result<T, Error>;

fn is_ident_start(c: char) -> bool {
    c.is_ascii_alphabetic() || c == '_'
}

fn is_ident(c: char) -> bool {
    is_ident_start(c) || c.is_ascii_digit()
}

pub struct Lexer<'a> {
    chars: Peekable<Chars<'a>>,
}

impl<'a> Lexer<'a> {
    pub fn new(source: &'a str) -> Self {
        Self {
            chars: source.chars().peekable(),
        }
    }

    fn skip_whitespace(&mut self) {
        while let Some(c) = self.chars.peek() {
            if c.is_whitespace() {
                self.chars.next();
            } else {
                break;
            }
        }
    }

    pub fn read_token(&mut self) -> Option<Token<'a>> {
        self.skip_whitespace();

        match self.chars.next()? {
            '{' => Some(Token::new(TokenKind::BraceLeft, "{")),
            '}' => Some(Token::new(TokenKind::BraceRight, "}")),
            '(' => Some(Token::new(TokenKind::ParenLeft, "(")),
            ')' => Some(Token::new(TokenKind::ParenRight, ")")),
            ';' => Some(Token::new(TokenKind::Semicolon, ";")),
        }
    }
}

impl<'a> Iterator for Lexer<'a> {
    type Item = Token<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        self.read_token()
    }
}

pub fn tokenize(source: &str) -> Result<Vec<Token>> {
    Lexer::new(source).collect()
}
