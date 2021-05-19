// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_WINDOW
#define H_SHIDO_WINDOW

#ifdef __cplusplus
extern "C"{
#endif

#include "../API.h"

SHIDO_HANDLE_H(Window)
// Create window.
// return new reference or NULL on failure (see shido_core_getError())
SHIDO_API shido_WindowRef* shido_Window_new(const char *title, int w, int h);
// Get window display.
// return 0-based index or < 0 on failure (error)
SHIDO_API int shido_Window_getDisplay(shido_Window *self);

#ifdef __cplusplus
}
#endif

#endif
