import pprint

import interpreter
import lexer
import parser

while True:
    try:
        source = input("> ")
    except EOFError:
        # Printing a newline makes the output look better since the shell
        # prompt won't reappear on the same line as the repl prompt.
        print()
        break

    try:
        tokens = list(lexer.tokenize(source))  
        tree = parser.parse(tokens)
    except lexer.LexError as e:
        print(f"LexError: {e}")
        continue
    except parser.ParseError as e:
        print(f"ParseError: {e}")
        continue

    pprint.pprint(tokens)
    pprint.pprint(tree)

    result = interpreter.Interpreter().evaluate(tree)
    print(result)
    
