// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_WINDOW
#define HPP_SHIDO_WINDOW

#include "../API.hpp"
#include "../core.hpp"
#include "Window.h"
#include <SDL2/SDL_video.h>

SHIDO_HANDLE_HPP(Window)

struct shido_Window{
  SDL_Window *handle;
  shido_Window(SDL_Window *_handle): handle(_handle){}
  ~shido_Window();
};

#endif
