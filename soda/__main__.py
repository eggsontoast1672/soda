import pprint

from . import interpreter
from . import lexer
from . import parser
from .util import SodaError

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
        result = interpreter.Interpreter().evaluate(tree)
    except SodaError as e:
        print(e.message)
        continue

    # pprint.pprint(tokens)
    # pprint.pprint(tree)
    pprint.pprint(result)
