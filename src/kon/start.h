#ifndef KON_START_H_
#define KON_START_H_

#if defined(__WIN32)
#define KON_WINDOWS
#elif defined(__linux__) || defined(__unix__)
#define KON_LINUX
#if defined(__ANDROID__)
#define KON_ANDROID
#endif
#elif defined(__EMSCRIPTEN__)
#define KON_EMSCRIPTEN
#elif defined(__APPLE__)
#define KON_APPLE
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define KON_IOS
#else
#define KON_MACOS
#endif
#else
#error "<kon/start.h> Unknown platform"
#endif

#ifndef KON_NO_AUTO_GRAPHICS_API

#if defined(KON_WINDOWS)
#ifdef KON_SOKOL_EXPERIMENTAL
#define KON_VULKAN
#else
#define KON_D3D11
#endif

#elif defined(KON_ANDROID)
#define KON_GLES3 

#elif defined(KON_LINUX)
#ifdef KON_SOKOL_EXPERIMENTAL
#define KON_VULKAN
#else
#define KON_GLCORE
#endif

#elif defined(KON_EMSCRIPTEN)
#ifdef KON_SOKOL_EXPERIMENTAL
#define KON_WGPU
#else
#define KON_GLES3
#endif

#elif defined(KON_IOS) || defined(KON_MACOS)
#define KON_METAL

#endif

#endif /* KON_NO_AUTO_GRAPHICS_API */

#if defined(KON_WINDOWS)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS (1)
#endif
#else
#define _POSIX_C_SOURCE 200809L
#endif

#define KON_UNUSED(v) (void)v

#endif /* KON_START_H_ */
