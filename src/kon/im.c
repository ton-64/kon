/*
  This file is used to load single header dependencies of Kon
 */
#include "start.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/image.h>

#if defined(KON_WINDOWS)
#ifdef KON_SOKOL_EXPERIMENTAL
#define SOKOL_VULKAN
#else
#define SOKOL_D3D11
#endif

#elif defined(KON_ANDROID)
#define SOKOL_GLES3 

#elif defined(KON_LINUX)
#ifdef KON_SOKOL_EXPERIMENTAL
#define SOKOL_VULKAN
#else
#define SOKOL_GLCORE
#endif

#elif defined(KON_EMSCRIPTEN)
#ifdef KON_SOKOL_EXPERIMENTAL
#define SOKOL_WGPU
#else
#define SOKOL_GLES3
#endif

#elif defined(KON_IOS) || defined(KON_MACOS)
#define SOKOL_METAL

#endif

#define SOKOL_IMPL
#include <sokol/log.h>

#define SOKOL_NO_ENTRY
#include <sokol/app.h>

#include <sokol/gfx.h>
#include <sokol/glue.h>
