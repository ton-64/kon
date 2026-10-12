#include "log.h"

#include <stdarg.h>
#include <stdio.h>

static void
defaultConsoleHook(kon_log_level_t log_level, const char* message) {
  char buf[256];

  const char* _; /* Im tired of naming things */
  switch (log_level) {
    case KON_DEBUG_LEVEL: _ = "debug"; break;
    case KON_INFO_LEVEL:  _ = "info";  break;
    case KON_WARN_LEVEL:  _ = "warn";  break;
    case KON_ERROR_LEVEL: _ = "error"; break;  
    default:
      return;
  }
  
  int n = snprintf(buf, sizeof buf, "kon %s : %s", _, message);
  fputs(buf, stderr);
  fputc('\n', stderr);  
}

kon_consoleHook kon_console_hook = defaultConsoleHook;

void
__kon_log(kon_log_level_t log_level, const char *format, ...) {
  if (!kon_console_hook || !kon_logEnabled(log_level))
    return;
  
  char buf[128]; /* 64 is enough */

  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof buf, format, args);
  va_end(args);
  
  kon_console_hook(log_level, buf);
}
