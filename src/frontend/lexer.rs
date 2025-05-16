use std::result;

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
    source: &'a str,
    start: usize,
    position: usize,
}

impl<'a> Lexer<'a> {
    pub const fn new(source: &'a str) -> Self {
        Self {
            source,
            start: 0,
            position: 0,
        }
    }

    fn peek_char(&self) -> Option<char> {
        self.source.chars().nth(self.position)
    }

    fn skip_whitespace(&mut self) {
        while let Some(c) = self.peek_char() {
            if c.is_whitespace() {
                self.read_char();
            } else {
                break;
            }
        }
    }

    fn make_token(&self, kind: TokenKind) -> Token<'a> {
        let lexeme = &self.source[self.start..self.position];
        Token::new(kind, lexeme)
    }

    fn match_token(
        &mut self,
        expected: char,
        primary: TokenKind,
        fallback: TokenKind,
    ) -> Token<'a> {
        match self.peek_char() {
            Some(c) if c == expected => {
                self.read_char();
                self.make_token(primary)
            }
            _ => self.make_token(fallback),
        }
    }

    fn read_char(&mut self) -> Option<char> {
        let next = self.source.chars().nth(self.position);
        if next.is_some() {
            self.position += 1;
        }
        next
    }

    pub fn read_token(&mut self) -> Option<Result<Token<'a>>> {
        self.skip_whitespace();
        self.start = self.position;

        let token = match self.read_char()? {
            '-' => Ok(self.make_token(TokenKind::Minus)),
            '%' => Ok(self.make_token(TokenKind::Percent)),
            '+' => Ok(self.make_token(TokenKind::Plus)),
            '/' => Ok(self.make_token(TokenKind::Slash)),
            '*' => Ok(self.make_token(TokenKind::Star)),
            '!' => Ok(self.match_token('=', TokenKind::BangEqual, TokenKind::Bang)),
            '=' => Ok(self.match_token('=', TokenKind::EqualEqual, TokenKind::Equal)),
            '>' => Ok(self.match_token('=', TokenKind::GreaterEqual, TokenKind::Greater)),
            '<' => Ok(self.match_token('=', TokenKind::LessEqual, TokenKind::Less)),
            c if is_ident_start(c) => self.read_ident(),
            c => Err(Error::new(c)),
        };

        Some(token)
    }
}

impl<'a> Iterator for Lexer<'a> {
    type Item = Result<Token<'a>>;

    fn next(&mut self) -> Option<Self::Item> {
        self.read_token()
    }
}

pub fn tokenize(source: &str) -> Result<Vec<Token>> {
    Lexer::new(source).collect()
}
