pub enum BinaryOperation {
    Plus,
    Minus,
    Times,
    Divided,
    Modulo,
}

pub enum Expr {
    Literal(f64),
    Binary {
        operator: BinaryOperation,
        left: Box<Expr>,
        right: Box<Expr>,
    },
}
