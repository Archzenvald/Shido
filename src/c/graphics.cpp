// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "graphics.hpp"

bool shido_graphics_init()
{
  int status = SDL_InitSubSystem(SDL_INIT_VIDEO);
  if(status != 0)
    std::cerr << "[shido] SDL2 graphics init failed: " << SDL_GetError() << std::endl;
  return status;
}
