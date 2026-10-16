#ifndef KON_FS_H_
#define KON_FS_H_

#include "start.h"

#include <stddef.h>
#include <stdbool.h>

bool kon_toExecDir();

/*
    @brief Make a directory if it doesnt exist yet.
 */
bool kon_makeDir(const char* path);

/*
    @brief Load a file
    @return NULL on failure.
 */
void* kon_loadFile(const char* path, size_t* out_size);

/*
    @brief Save a file; it the file doesnt exist, then make one
 */
bool kon_saveFile(const char* path, const void* data, size_t size);

#endif /* KON_FS_H_ */
