/*
  <kon/log.h> - Kon's logger
 */
#ifndef KON_LOG_H_
#define KON_LOG_H_

#include "start.h"

typedef enum {
  KON_DEBUG_LEVEL,
  KON_INFO_LEVEL,
  KON_WARN_LEVEL,
  KON_ERROR_LEVEL
} kon_log_level_t;
KON_API extern kon_log_level_t kon_min_log_level;

#define kon_logEnabled(level)     ((level) > kon_min_log_level)

typedef void (*kon_consoleHook)(kon_log_level_t log_level, const char* message);
KON_API extern kon_consoleHook kon_console_hook;

#ifdef KON_DEBUG
#define kon_debugLog(format, ...) __kon_log(KON_DEBUG_LEVEL, format, ##__VA_ARGS__)
#else
#define kon_debugLog(format, ...) ((void)0)
#endif
#define kon_infoLog(format, ...)  __kon_log(KON_INFO_LEVEL, format, ##__VA_ARGS__)
#define kon_warnLog(format, ...)  __kon_log(KON_WARN_LEVEL, format, ##__VA_ARGS__)
#define kon_errorLog(format, ...) __kon_log(KON_ERROR_LEVEL, format, ##__VA_ARGS__)

KON_API void __kon_log(kon_log_level_t log_level, const char* format, ...);

#endif /* KON_LOG_H_ */
