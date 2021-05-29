// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

// API helper.
#ifndef H_SHIDO_API
#define H_SHIDO_API

#include <stdbool.h>
#include <stdint.h>

// Export.
#ifdef _WIN32
  #define SHIDO_API __declspec(dllexport)
#else
  #define SHIDO_API __attribute__((visibility("default")))
#endif

// Generate handles API.
//
// typedef struct shido_T shido_T;
// typedef struct shido_TRef shido_TRef;
// shido_TRef* shido_TRef_new(shido_TRef*);
// shido_T* shido_TRef_ptr(shido_TRef*);
// void shido_TRef_free(shido_TRef*);
#define SHIDO_HANDLE_H(T) typedef struct shido_ ## T shido_ ## T; \
  typedef struct shido_ ## T ## Ref shido_ ## T ## Ref; \
  SHIDO_API shido_ ## T ## Ref* shido_ ## T ## Ref ## _new(shido_ ## T ## Ref*); \
  SHIDO_API shido_ ## T* shido_ ## T ## Ref ## _ptr(shido_ ## T ## Ref*); \
  SHIDO_API void shido_ ## T ## Ref ## _free(shido_ ## T ## Ref*);

#endif
