/*
    This file is used to load single header dependencies of Kon
 */
#include "start.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/image.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include <nuklear/nuklear.h>

#if defined(KON_GLCORE)
#define SOKOL_GLCORE
#elif defined(KON_GLES3)
#define SOKOL_GLES3
#elif defined(KON_D3D11)
#define SOKOL_D3D11
#elif defined(KON_METAL)
#define SOKOL_METAL
#elif defined(KON_VULKAN)
#define SOKOL_VULKAN
#elif defined(KON_WGPU)
#define SOKOL_WGPU
#endif

#define SOKOL_IMPL
#include <sokol/log.h>

#define SOKOL_NO_ENTRY
#include <sokol/app.h>

#include <sokol/gfx.h>
#include <sokol/glue.h>

#include <sokol/util/nuklear.h>
