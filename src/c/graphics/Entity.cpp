// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "Entity.hpp"

SHIDO_HANDLE_CPP(Entity)

shido_Entity::~shido_Entity()
{
  shido::Graphics &graphics = shido::Graphics::get();
  graphics.engine->destroy(handle);
  graphics.entity_manager.destroy(handle);
}

shido_EntityRef* shido_Entity_new()
{
  utils::Entity handle = shido::Graphics::get().entity_manager.create();
  if(handle.isNull()){
    shido::error("Filament Entity creation failed.");
    return nullptr;
  }
  return new shido_EntityRef{std::make_shared<shido_Entity>(handle)};
}
