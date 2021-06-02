// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_SCENE
#define HPP_SHIDO_SCENE

#include "Scene.h"

#include "../API.hpp"
#include "../graphics.hpp"
#include <filament/Scene.h>

SHIDO_HANDLE_HPP(Scene)

struct shido_Scene{
  filament::Scene *handle;
  shido_Scene(filament::Scene *_handle): handle(_handle){}
  ~shido_Scene();
};

#endif
