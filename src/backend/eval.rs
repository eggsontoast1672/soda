use crate::frontend::ast::{BinaryOperation, Expr};

fn combine(operator: BinaryOperation, left: f64, right: f64) -> f64 {
    match operator {
        BinaryOperation::Plus => left + right,
        BinaryOperation::Minus => left - right,
        BinaryOperation::Times => left * right,
        BinaryOperation::Divided => left / right,
        BinaryOperation::Modulo => left % right,
    }
}

pub fn evaluate(expr: Expr) -> f64 {
    match expr {
        Expr::Literal(value) => value,
        Expr::Binary {
            operator,
            left,
            right,
        } => {
            let left = evaluate(*left);
            let right = evaluate(*right);
            combine(operator, left, right)
        }
    }
}
