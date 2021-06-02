// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "View.hpp"

SHIDO_HANDLE_CPP(View)

shido_View::~shido_View()
{
  shido::Graphics::get().engine->destroy(handle);
}

shido_ViewRef* shido_View_new()
{
  filament::View *handle = shido::Graphics::get().engine->createView();
  if(!handle){
    shido::error("Filament View creation failed.");
    return nullptr;
  }
  return new shido_ViewRef{std::make_shared<shido_View>(handle)};
}
