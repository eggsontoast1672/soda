# Soda

This project intends to implement a compiler for a heavily reduced subset of
Rust which includes garbage collection. This idea came about rather naturally
while doing some Rust programming. I realized that I love Rust, but I don't
care for the borrow checker all the time. Sometimes, I want to ignore
performance and just have fun writing a program. That is the idea resting at
the heart of soda.

At the moment, the syntax of the language is exactly the following:

```rust
fn main() {
    return number;
}
```

Where `number` is some integer constant. This exact code will be compiled into
an assembly file which loads the number into the `rdi` register and does an
exit syscall. It really is that shitty.

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

- [ ] Improve lexer error messages
- [ ] Improve parser error messages
- [ ] Add documentation all around

## License

This project is licensed under the MIT license. Do what you will with the code,
but make sure that I am always properly credited. For more information, see the
Open Source Initiative website.
