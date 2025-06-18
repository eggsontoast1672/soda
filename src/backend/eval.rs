use crate::frontend::ast::{BinaryOp, Expr, UnaryOp, Value};

pub fn evaluate(expr: Expr) -> Value {
    match expr {
        Expr::Literal(value) => value,
        Expr::Unary { operator, right } => eval_unary(operator, *right),
        Expr::Binary {
            operator,
            left,
            right,
        } => {
            let left = evaluate(*left);
            let right = evaluate(*right);
            eval_binary(operator, left, right)
        }
    }
}

fn eval_binary(operator: BinaryOp, left: Value, right: Value) -> Value {
    match (operator, left, right) {
        (BinaryOp::Plus, Value::Number(x), Value::Number(y)) => Value::Number(x + y),
        (BinaryOp::Minus, Value::Number(x), Value::Number(y)) => Value::Number(x - y),
        (BinaryOp::Times, Value::Number(x), Value::Number(y)) => Value::Number(x * y),
        (BinaryOp::Divided, Value::Number(x), Value::Number(y)) => Value::Number(x / y),
        (BinaryOp::Modulo, Value::Number(x), Value::Number(y)) => Value::Number(x % y),
        (BinaryOp::Equal, Value::Boolean(x), Value::Boolean(y)) => Value::Boolean(x == y),
        _ => todo!(),
    }
}

fn eval_unary(operator: UnaryOp, right: Expr) -> Value {
    let value = evaluate(right);
    match (operator, value) {
        (UnaryOp::Negative, Value::Number(x)) => Value::Number(-x),
        (UnaryOp::Not, Value::Boolean(x)) => Value::Boolean(!x),
        _ => panic!("type error"),
    }
}
