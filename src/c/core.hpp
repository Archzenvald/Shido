// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_CORE
#define HPP_SHIDO_CORE

#include "core.h"
#include <iostream>
#include <utils/Path.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

// Core state.
struct Core{
  Core();
  ~Core();
  static Core& get();
  //
  int status;
};

#endif
