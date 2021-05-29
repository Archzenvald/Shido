// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_GRAPHICS
#define H_SHIDO_GRAPHICS

#ifdef __cplusplus
extern "C"{
#endif

#include "API.h"
#include <SDL2/SDL_video.h>

typedef struct shido_Display_t{
  const char *name; // can be NULL
  int x, y, w, h; // bounds
  int ux, uy, uw, uh; // usable bounds
  bool has_dpi;
  float ddpi, hdpi, vdpi; // diagonal, horizontal, vertical DPIs
} shido_Display_t;

// Init.
// return false on failure (error)
SHIDO_API bool shido_graphics_init();
SHIDO_API int shido_graphics_getDisplayCount();
// Get display info.
// index: 0-based
SHIDO_API void shido_graphics_getDisplay(int index, shido_Display_t *out);
SHIDO_API int shido_graphics_getDisplayModeCount(int index);
// index: 0-based
// mode_index: 0-based, -1 to get the desktop mode
// return false on failure
SHIDO_API bool shido_graphics_getDisplayMode(int index, int mode_index, SDL_DisplayMode *out);

#ifdef __cplusplus
}
#endif

#endif
