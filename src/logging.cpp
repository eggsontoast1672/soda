#include "soda/logging.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace soda {

void log_fatal(const char *fmt...) {
  va_list args;
  va_start(args, fmt);
  std::fprintf(stderr, "FATAL\t");
  std::vfprintf(stderr, fmt, args);
  va_end(args);
  std::exit(1);
}

} // namespace soda
