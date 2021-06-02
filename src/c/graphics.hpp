// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_GRAPHICS
#define HPP_SHIDO_GRAPHICS

#include "graphics.h"
#include "core.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <filament/Engine.h>
#include <utils/EntityManager.h>

namespace shido{

// Module state.
struct Graphics{
  Graphics();
  ~Graphics();
  static Graphics& get();
  //
  bool ok;
  std::string err;
  filament::Engine *engine;
  utils::EntityManager &entity_manager;
};

}

#endif
