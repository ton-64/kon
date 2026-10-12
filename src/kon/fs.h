/*
  <kon/fs.h> - Kon's minimal file system
 */
#ifndef KON_FS_H_
#define KON_FS_H_

#include "start.h"

#include <stddef.h>
#include <stdbool.h>

/*
  @brief Make a directory if it doesnt exist yet.
 */
KON_API bool kon_makeDirectory(const char* path);

/*
  @brief Load a file
  @return NULL on failure.
 */
KON_API char* kon_loadFile(const char* path, size_t* out_size);

/*
  @brief Save a file; it the file doesnt exist, then make one
 */
KON_API bool kon_saveFile(const char* path, const char* data, size_t size);

#endif /* KON_FS_H_ */
