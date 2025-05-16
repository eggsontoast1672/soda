use std::io::{self, Write};

use soda::frontend::lexer;

fn get_line(prompt: &str) -> io::Result<Option<String>> {
    print!("{}", prompt);
    io::stdout().flush()?;
    io::stdin()
        .lines()
        .next()
        .map_or(Ok(None), |line| line.map(Some))
}

pub fn start() {
    loop {
        let line = match get_line(">>> ") {
            Ok(Some(line)) => line,
            Ok(None) => break,
            Err(e) => {
                println!("Failed to read line: {}", e);
                continue;
            }
        };

        match lexer::tokenize(&line) {
            Ok(tokens) => println!("{:?}", tokens),
            Err(e) => println!(
                "Failed to tokenize line: unrecognized token '{}'",
                e.character
            ),
        }
    }
}
