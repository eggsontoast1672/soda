#[derive(Debug)]
pub enum TokenKind {
    BraceLeft,
    BraceRight,
    ParenLeft,
    ParenRight,
    Semicolon,
    Identifier,
    Fn,
    Return,
}

impl TokenKind {
    pub fn ident(lexeme: &str) -> Self {
        match lexeme {
            "fn" => Self::Fn,
            "return" => Self::Return,
            _ => Self::Identifier,
        }
    }
}

#[derive(Debug)]
pub struct Token<'a> {
    pub kind: TokenKind,
    pub lexeme: &'a str,
}

impl<'a> Token<'a> {
    pub const fn new(kind: TokenKind, lexeme: &'a str) -> Self {
        Self { kind, lexeme }
    }
}
