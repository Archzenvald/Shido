// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_API
#define H_SHIDO_API

#include <stdbool.h>

#ifdef _WIN32
  #define API __declspec(dllexport)
#else
  #define API __attribute__((visibility("default")))
#endif

#endif
