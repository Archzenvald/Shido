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
