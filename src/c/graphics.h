// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_GRAPHICS
#define H_SHIDO_GRAPHICS

#ifdef __cplusplus
extern "C"{
#endif

#include "API.h"

typedef struct shido_Display_t{
  const char *name; // can be NULL
  int x, y, w, h; // bounds
  int ux, uy, uw, uh; // usable bounds
  bool has_dpi;
  float ddpi, hdpi, vdpi; // diagonal, horizontal, vertical DPIs
} shido_Display_t;

SHIDO_API bool shido_graphics_init();
SHIDO_API int shido_graphics_getDisplayCount();
// Get display info.
SHIDO_API void shido_graphics_getDisplay(int index, shido_Display_t *out);

#ifdef __cplusplus
}
#endif

#endif
