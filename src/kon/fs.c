#include "fs.h"
#include "log.h"

#include <stdlib.h>
#include <string.h> /* For strerror() */
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#if defined(KON_WINDOWS)
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif

bool
kon_makeDirectory(const char* path) {
  int res;
#if defined(KON_WINDOWS)
  res = _mkdir(path, 0755);
#else
  res = mkdir(path, 0755);
#endif
  if (res < 0) {
    if (errno == EEXIST) {
      kon_debugLog("Directory '%s' already exists", path);
      return true;
    }
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to create directory '%s' : %s", path, strerror(errno));
    return false;
  }
  kon_infoLog(KON_LOG_TAG_DEFAULT, "Create directory '%s'", path);
  return true;
}

char*
kon_loadFile(const char* path, size_t* out_size) {
  int fd;
#if defined(KON_WINDOWS)
  fd = _open(path, _O_RDONLY | _O_BINARY);
#else
  fd = open(path, O_RDONLY);
#endif
  if (fd < 0) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to load '%s' : %s", path, strerror(errno));
    return NULL;
  }

  struct stat st;
  int st_res;
#if defined(KON_WINDOWS)
  st_res = _fstat(fd, &st);
#else 
  st_res = fstat(fd, &st);
#endif
  if (st_res < 0) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to load '%s' because file metadata could not be read : %s", path, strerror(errno));
    return NULL;
  }
  size_t file_size = (size_t)st.st_size;
  
  size_t read_size = 0;
  char* read_data = malloc(file_size);
  if (!read_data) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to load '%s' because read data could not be allocated : %s", path, strerror(errno));
    return NULL;
  }
  
  for (;;) {
    size_t rem = file_size - read_size;

#if defined(KON_WINDOWS)
    int n = _read(fd, read_data + read_size, rem);
#else
    ssize_t n = read(fd, read_data + read_size, rem);
#endif
    if (n > 0) {
      read_size += n;
    } else if(errno == EINTR) {
      kon_errorLog(KON_LOG_TAG_DEFAULT, "_read() | read() was interrupted. ");
      break;
    } else {
      break;
    }
  }
  if (read_size != file_size) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Incomplete load for '%s' : expected %zu bytes, got %zu", path, file_size, read_size);
    free(read_data);
#if defined(KON_WINDOWS)
    _close(fd);
#else
    close(fd);
#endif
    return NULL;
  }    
  kon_infoLog(KON_LOG_TAG_DEFAULT, "Successfully loaded '%s'", path);

#if defined(KON_WINDOWS)
  _close(fd);
#else
  close(fd);
#endif

  if (out_size)
    *out_size = read_size;
  
  return read_data;
}

bool
kon_saveFile(const char* path, const char* data, size_t size) {
  int fd;
#if defined(KON_WINDOWS)
  fd = _open(path, _O_CREAT | _O_TRUNC | _O_WRONLY | _O_BINARY, _S_IWRITE);/* Holy fucking shit Win32 */
#else
  fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
#endif
  if (fd < 0) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to save '%s' : %s", path, strerror(errno));
    return false;
  }
  
  size_t write_size = 0;
  for (;;) {
    size_t rem = size - write_size;

#if defined(KON_WINDOWS)
    int n = _write(fd, data + write_size, rem);
#else
    ssize_t n = write(fd, data + write_size, rem);    
#endif

    if (n > 0) {
      write_size += n;
    } else if (errno == EINTR) {
      kon_debugLog(KON_LOG_TAG_DEFAULT, "_write | write got interrupted");
    } else {
      break;
    }
  }
  if (write_size != size) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Incomplete save for '%s': expected %zu bytes, wrote %zu", path, size, write_size);
  }

#if defined(KON_WINDOWS)
  int a = _close(fd);
#else
  int a = close(fd);
#endif
  if (a < 0) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to close '%s' : %s", path, strerror(errno));
    return false;
  }
  
  kon_infoLog(KON_LOG_TAG_DEFAULT, "Successfully saved '%s'", path);
  
  return true;
}
