// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_CORE
#define HPP_SHIDO_CORE

#include "core.h"
#include <utils/Path.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#endif

namespace shido{

// Error handling.
void error(const std::string& err);
const std::string& getError();

// Core state.
struct Core{
  Core();
  ~Core();
  static Core& get();
  //
  bool ok;
};

}

#endif
