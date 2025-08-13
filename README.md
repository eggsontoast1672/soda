# Soda

This project intends to implement an interpreter for a modified version of the
Rust programming language, using a garbage collector in lieu of the borrow
checker. This idea came about rather naturally while doing some Rust
programming. I realized that I love Rust, but I don't care for the borrow
checker all the time. Sometimes, I just want to write code in a pedantic and
featureful language, without worrying about memory safety. For the joy of
programming, I suppose.

I had originally intended to make this language compiled instead of
interpreted, but I realized that it was too much work for the end result that I
wanted, so I settled on this.

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
