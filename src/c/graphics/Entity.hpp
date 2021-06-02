// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_ENTITY
#define HPP_SHIDO_ENTITY

#include "Entity.h"

#include "../API.hpp"
#include "../graphics.hpp"
#include <utils/Entity.h>

SHIDO_HANDLE_HPP(Entity)

struct shido_Entity{
  utils::Entity handle;
  shido_Entity(utils::Entity _handle): handle(_handle){}
  ~shido_Entity();
};

#endif
