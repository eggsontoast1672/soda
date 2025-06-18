pub fn compile(exit_code: u8) -> String {
    let mut assembly = String::from("global _start\n\nsection .text\n_start:\n");
    assembly.push_str("\tmov rax, 0x3c\t; exit syscall\n");
    let exit_line = format!("\tmov rdi, {}\n", exit_code);
    assembly.push_str(&exit_line);
    assembly.push_str("\tsyscall\n");
    assembly
}
