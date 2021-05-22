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
// Get window from id.
// return new reference or NULL
SHIDO_API shido_WindowRef* shido_Window_get(uint32_t id);
// Get window display.
// return 0-based index or < 0 on failure (error)
SHIDO_API int shido_Window_getDisplayIndex(shido_Window *self);
SHIDO_API bool shido_Window_hasInputGrab(shido_Window *self);
SHIDO_API void shido_Window_getMinimumSize(shido_Window *self, int out[2]);
SHIDO_API void shido_Window_getMaximumSize(shido_Window *self, int out[2]);
SHIDO_API float shido_Window_getOpacity(shido_Window *self);
SHIDO_API void shido_Window_getPosition(shido_Window *self, int out[2]);
SHIDO_API void shido_Window_getSize(shido_Window *self, int out[2]);
SHIDO_API const char* shido_Window_getTitle(shido_Window *self);
SHIDO_API void shido_Window_hide(shido_Window *self);
SHIDO_API void shido_Window_show(shido_Window *self);
SHIDO_API void shido_Window_maximize(shido_Window *self);
SHIDO_API void shido_Window_minimize(shido_Window *self);
SHIDO_API void shido_Window_raise(shido_Window *self);
SHIDO_API void shido_Window_restore(shido_Window *self);
// Set window fullscreen state.
// desktop: true for non-exclusive desktop/windowed fullscreen
// return false on failure (error)
SHIDO_API bool shido_Window_setFullscreen(shido_Window *self, bool enable, bool desktop);
// Set fullscreen display mode.
// return false on failure (error)
SHIDO_API bool shido_Window_setDisplayMode(shido_Window *self, const SDL_DisplayMode *mode);

SHIDO_API void shido_Window_setInputGrab(shido_Window *self, bool enable);
SHIDO_API void shido_Window_setResizable(shido_Window *self, bool flag);
SHIDO_API void shido_Window_setBordered(shido_Window *self, bool flag);
SHIDO_API void shido_Window_setOpacity(shido_Window *self, float opacity);
SHIDO_API void shido_Window_setMinimumSize(shido_Window *self, int w, int h);
SHIDO_API void shido_Window_setMaximumSize(shido_Window *self, int w, int h);
SHIDO_API void shido_Window_setSize(shido_Window *self, int w, int h);
SHIDO_API void shido_Window_setPosition(shido_Window *self, int x, int y);
SHIDO_API void shido_Window_setTitle(shido_Window *self, const char *title);

// out: filled with fullscreen and desktop flag
SHIDO_API void shido_Window_getFullscreen(shido_Window *self, bool out[2]);
SHIDO_API bool shido_Window_isVisible(shido_Window *self);
SHIDO_API bool shido_Window_isResizable(shido_Window *self);
SHIDO_API bool shido_Window_isBordered(shido_Window *self);
SHIDO_API bool shido_Window_isMaximized(shido_Window *self);
SHIDO_API bool shido_Window_isMinimized(shido_Window *self);
SHIDO_API bool shido_Window_hasFocus(shido_Window *self);
SHIDO_API bool shido_Window_hasMouseFocus(shido_Window *self);

#ifdef __cplusplus
}
#endif

#endif
