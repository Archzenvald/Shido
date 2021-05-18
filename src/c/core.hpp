// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

/*
 * Each component of the API, like a module or handle, can be made up of multiple files:
 * - name.h: The C API.
 * - name.hpp: The implementation header.
 * - name.cpp: The implementation.
 * - name.lua: The Lua API/implementation.
 *
 * For the C++ implementation, the shido:: namespace is used to avoid
 * collisions; module/handle namespaces may be overkill.
 */

#ifndef HPP_SHIDO_CORE
#define HPP_SHIDO_CORE

#include "core.h"
#include <iostream>
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
void warning(const std::string& warn);

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
