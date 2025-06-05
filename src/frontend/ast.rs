pub enum Value {
    Number(f64),
    Boolean(bool),
}

pub enum UnaryOp {
    Negative,
    Not,
}

#[rustfmt::skip]
pub enum BinaryOp {
    // Numeric operations
    Plus, Minus, Times, Divided, Modulo,

    // Boolean operations
    Equal, NotEqual,
    Less, LessEqual,
    Greater, GreaterEqual,
    And, Or,
}

pub enum Expr {
    Literal(Value),
    Unary {
        operator: UnaryOp,
        right: Box<Expr>,
    },
    Binary {
        operator: BinaryOp,
        left: Box<Expr>,
        right: Box<Expr>,
    },
}
