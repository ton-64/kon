/*
  <kon/start.h> - Starter for Kon's header files
 */
#ifndef KON_START_H_
#define KON_START_H_

#ifdef KON_BUILD_DLL
#ifdef _MSC_VER
#define KON_API __declspec(dllexport)
#else
#define KON_API __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
#define KON_API __declspec(dllimport)
#else
#define KON_API
#endif
#endif

#ifndef NDEBUG
#define KON_DEBUG
#else
#define KON_RELEASE
#endif

#ifdef _WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#endif /* KON_START_H_ */
