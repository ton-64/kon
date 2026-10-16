#ifndef KON_IMAGE_H_
#define KON_IMAGE_H_

#include "../start.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct kon_image {
  unsigned char* pixels;
    
  int width;
  int height;
  int channels;
  bool load;
} kon_image_t;

/*
    @brief Load a image
 */
kon_image_t kon_loadImageFromMemory(const void* data, size_t size, int desired_channels);

/*
    @brief Free the image data and set all to 0
 */
void kon_freeImage(kon_image_t* img);

#endif /* KON_IMAGE_H_ */
