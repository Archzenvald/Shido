// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "input.hpp"

bool shido_input_init()
{
  bool ok = (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == 0);
  if(!ok)
    shido::error(std::string("SDL input init failed: ")+SDL_GetError());
  return ok;
}

SDL_Keycode shido_input_getKeyFromScancode(SDL_Scancode scancode)
{ return SDL_GetKeyFromScancode(scancode); }

SDL_Scancode shido_input_getScancodeFromKey(SDL_Keycode keycode)
{ return SDL_GetScancodeFromKey(keycode); }

const Uint8* shido_input_getKeyboardState()
{ return SDL_GetKeyboardState(nullptr); }

bool shido_input_hasScreenKeyboard()
{ return SDL_HasScreenKeyboardSupport(); }

bool shido_input_isTextInputActive()
{ return SDL_IsTextInputActive(); }

void shido_input_startTextInput(){ SDL_StartTextInput(); }
void shido_input_stopTextInput(){ SDL_StopTextInput(); }
void shido_input_setTextInputRect(int x, int y, int w, int h)
{
  SDL_Rect rect{.x = x, .y = y, .w = w, .h = h};
  SDL_SetTextInputRect(&rect);
}

SDL_Keymod shido_input_getKeyboardMod()
{ return SDL_GetModState(); }
