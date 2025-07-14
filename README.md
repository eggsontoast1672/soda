# Soda

This project intends to implement a compiler for a heavily reduced subset of
Rust, minus the borrow checker in particular. This idea came about rather
naturally while doing some Rust programming. I realized that I love Rust, but I
don't care for the borrow checker all the time. Sometimes, I just want to write
code in a pedantic and featureful language, without worrying about memory
safety. For the joy of programming, I suppose.

At the moment, the language supports function declarations, compound and return
statements, as well as identifier and integer literal expressions. My main goal
is to finish the compiler pipeline so that I have something that works, then go
from there.

```rust
// Should generate something along the lines of:
//
//   .globl _start
// _start:
//   movl $0x3c, %eax
//   movl $69, %edi
//   syscall

fn main() -> i32 {
    return 69;
}
```

While I originally wanted to write the backend myself, I decided that it would
just be too much to take on. For practical and educational purposes, I have
opted to use LLVM for the backend. This will make things easier on me since I
don't have to write the middle and back ends from scratch, and it will make the
language faster since LLVM can take care of optimization.

## Compiling

To compile this project, you need a C++ compiler, some sort of build backend
such as make, ninja, or any other generator that CMake supports, and CMake
itself. Just do the classic CMake incantation in the root of the project:

```bash
cmake -S . -B build
cmake --build build
build/soda
```

## Todo List

Here is the docket at the moment:

- [ ] Finish compiler pipeline
- [ ] Improve lexer error messages
- [ ] Improve parser error messages
- [ ] Add documentation all around

## License

This project is licensed under the MIT license. Do what you will with the code,
but make sure that I am always properly credited. For more information, see the
Open Source Initiative website.
