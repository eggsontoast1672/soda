#ifndef SODA_LOGGING_HPP
#define SODA_LOGGING_HPP

namespace soda {

void log_error(const char *fmt...);
[[noreturn]] void log_fatal(const char *fmt...);

} // namespace soda

#endif
