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

#ifdef __cplusplus
}
#endif

#endif
