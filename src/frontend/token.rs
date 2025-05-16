#[derive(Debug)]
pub enum TokenKind {
    // Single character
    Minus,
    Percent,
    Plus,
    Slash,
    Star,

    // One or two characters
    Bang,
    BangEqual,
    Equal,
    EqualEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,

    // Variadic length
    Ident,
    Number,

    // Keywords
    And,
    False,
    Or,
    True,
}

impl TokenKind {
    pub fn ident(lexeme: &str) -> Self {
        match lexeme {
            "and" => Self::And,
            "false" => Self::False,
            "or" => Self::Or,
            "true" => Self::True,
            _ => Self::Ident,
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
