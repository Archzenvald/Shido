// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "graphics.hpp"

bool shido_graphics_init()
{
  bool ok = (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0);
  if(!ok)
    shido::error(std::string("SDL2 graphics init failed: ")+SDL_GetError());
  return ok;
}
