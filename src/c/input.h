// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_INPUT
#define H_SHIDO_INPUT

#ifdef __cplusplus
extern "C"{
#endif

#include "API.h"
#include <SDL2/SDL_keyboard.h>

SHIDO_API bool shido_input_init();
SHIDO_API const Uint8* shido_input_getKeyboardState();
SHIDO_API SDL_Keymod shido_input_getKeyboardMod();
SHIDO_API SDL_Keycode shido_input_getKeyFromScancode(SDL_Scancode scancode);
SHIDO_API SDL_Scancode shido_input_getScancodeFromKey(SDL_Keycode keycode);
SHIDO_API bool shido_input_hasScreenKeyboard();
SHIDO_API bool shido_input_isTextInputActive();
SHIDO_API void shido_input_setTextInputRect(int x, int y, int w, int h);
SHIDO_API void shido_input_startTextInput();
SHIDO_API void shido_input_stopTextInput();

#ifdef __cplusplus
}
#endif

#endif
