use std::{fs::File, io::Write, os::unix::fs::PermissionsExt};

use soda::backend::compiler;

fn main() {
    let assembly = compiler::compile(0);
    let mut file = File::create("a.asm").unwrap();
    file.write_all(assembly.as_bytes()).unwrap();
}
