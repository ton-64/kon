#include "image.h"
#include "../log.h"

#include <stb/image.h>

kon_image_t
kon_loadImageFromMemory(const void* data, size_t size, int desired_channels) {
  kon_image_t img = {0};
  
  unsigned char* pixels = stbi_load_from_memory(
    (const stbi_uc*)data,
    (int)size,
    &img.width,
    &img.height,
    &img.channels,
    desired_channels
  );
  if (!pixels) {
    kon_errorLog(KON_LOG_TAG_STB, "Failed to load image : %s", stbi_failure_reason());
    return img;
  }
  img.load = true;
  
  kon_infoLog(KON_LOG_TAG_STB, "Successfully loaded image");
  
  return img;
}

void
kon_freeImage(kon_image_t* img) {
  if (!img->pixels)
    return; 
  stbi_image_free(img->pixels);
  img = (kon_image_t*){0}; /* Already sets load to false */
}
