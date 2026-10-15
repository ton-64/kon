#ifndef KON_LOG_H_
#define KON_LOG_H_

#include "start.h"

typedef enum kon_log_tag {
  KON_LOG_TAG_DEFAULT,

  KON_LOG_TAG_RESERVE_1,
  KON_LOG_TAG_RESERVE_2,
  KON_LOG_TAG_RESERVE_3,
  KON_LOG_TAG_RESERVE_4,
  KON_LOG_TAG_RESERVE_5,
  KON_LOG_TAG_RESERVE_6,
  KON_LOG_TAG_RESERVE_7,
  KON_LOG_TAG_RESERVE_8,

  _KON_LOG_TAG_FORCE_U32 = 0x7FFFFFFF
} kon_log_tag_t;

typedef enum kon_log_level {
  KON_LOG_LEVEL_PANIC,
  KON_LOG_LEVEL_ERROR,
  kON_LOG_LEVEL_WARN,
  KON_LOG_LEVEL_INFO,
    
  _KON_LOG_LEVEL_FORCE_U32 = 0x7FFFFFFF
} kon_log_level_t;
extern kon_log_level_t kon_min_log_level;

/* @brief Checks the log level if its greater than the minimal log level */
#define kon_logEnabled(level) (level >= kon_min_log_level) 

/* @brief Recieve a log message for you to output */
typedef void (*kon_logRecv)(
  const char* file_name,
  int line_nr,
  kon_log_tag_t tag,
  kon_log_level_t level,
  const char* message
);
extern kon_logRecv kon_log_recv;

#define kon_errorLog(tag, format, ...) __kon_log(__FILE__, __LINE__, (tag), KON_LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define kon_warnLog(tag, format, ...)  __kon_log(__FILE__, __LINE__, (tag), KON_LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define kon_infoLog(tag, format, ...)  __kon_log(__FILE__, __LINE__, (tag), KON_LOG_LEVEL_INFO, format, ##__VA_ARGS__)

#if !defined(KON_DEBUG)
#define kon_debugLog(tag, format, ...) __kon_log(__FILE__, __LINE__, (tag), KON_LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#else
#define kon_debugLog(tag, format, ...) ((void)0)
#endif

void __kon_log(
  const char* file_name,
  int line_nr,
  kon_log_tag_t tag,
  kon_log_level_t level,
  const char* format,
  ...
);

#endif /* KON_LOG_H_ */
