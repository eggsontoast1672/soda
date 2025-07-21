add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/src/lex.yy.cpp
  COMMAND flex -o ${CMAKE_SOURCE_DIR}/src/lex.yy.cpp ${CMAKE_SOURCE_DIR}/soda.l
  DEPENDS soda.l
)

# We cannot control what flex generates, so ensure that if it generates a
# function that is not used, that it is not reported as a warning.
set_source_files_properties(src/lex.yy.cpp PROPERTIES COMPILE_FLAGS -Wno-unused-function)

add_executable(
  soda
  src/fs.cpp
  src/lex.yy.cpp
  src/logging.cpp
  src/main.cpp
  src/options.cpp
  src/parser.cpp
  src/token.cpp
)

target_compile_options(soda PRIVATE -Wall -Wextra -pedantic)
target_include_directories(soda PRIVATE include)
