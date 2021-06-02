// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "Scene.hpp"

SHIDO_HANDLE_CPP(Scene)

shido_Scene::~shido_Scene()
{
  shido::Graphics::get().engine->destroy(handle);
}

shido_SceneRef* shido_Scene_new()
{
  filament::Scene *handle = shido::Graphics::get().engine->createScene();
  if(!handle){
    shido::error("Filament Scene creation failed.");
    return nullptr;
  }
  return new shido_SceneRef{std::make_shared<shido_Scene>(handle)};
}
