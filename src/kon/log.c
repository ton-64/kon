#include "log.h"

#include <sokol/log.h>

#include <stdarg.h>
#include <stdio.h>

static void
defaultRecv(
  const char* file_name,
  int line_nr,
  kon_log_tag_t tag,
  kon_log_level_t level,
  const char* message
) {  
  slog_func(NULL, (uint32_t)level, 0, message, line_nr, file_name, NULL);
}

kon_logRecv recv = defaultRecv;

void
__kon_log(
  const char* file_name,
  int line_nr,
  kon_log_tag_t tag,
  kon_log_level_t level,
  const char* format,
  ...
) {
  if (!recv || !kon_logEnabled(level))
    return;

  char buf[128];
  va_list args;
  va_start(args, format);
  int n = vsnprintf(buf, sizeof buf, format, args);
  va_end(args);

  if (n > 0) {
    recv(file_name, line_nr, tag, level, buf);
  }
}
