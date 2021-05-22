// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "input.hpp"

bool shido_input_init()
{
  bool ok = (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == 0);
  if(!ok)
    shido::error(std::string("SDL: ")+SDL_GetError());
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

void shido_input_getMousePosition(int out[2])
{ SDL_GetMouseState(out, out+1); }

Uint32 shido_input_getMouseState()
{ return SDL_GetMouseState(nullptr, nullptr); }

void shido_input_warpMouse(int x, int y, shido_Window *window)
{ SDL_WarpMouseInWindow(window ? window->handle : nullptr, x, y); }

bool shido_input_setRelativeMouseMode(bool enable)
{
  bool ok = (SDL_SetRelativeMouseMode(enable ? SDL_TRUE : SDL_FALSE) == 0);
  if(!ok)
    shido::error(std::string("SDL: ")+SDL_GetError());
  return ok;
}

bool shido_input_getRelativeMouseMode()
{ return SDL_GetRelativeMouseMode(); }
