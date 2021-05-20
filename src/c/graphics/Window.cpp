// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "Window.hpp"

SHIDO_HANDLE_CPP(Window)

shido::Registry<SDL_Window*, shido_WindowRef>& shido_Window::getRegistry()
{
  static shido::Registry<SDL_Window*, shido_WindowRef> registry;
  return registry;
}

shido_Window::~shido_Window()
{
  shido_Window::getRegistry().unreg(handle);
  SDL_DestroyWindow(handle);
}

shido_WindowRef* shido_Window_new(const char *title, int w, int h)
{
  SDL_Window *handle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
  if(!handle){
    shido::error(std::string("SDL: ")+SDL_GetError());
    return nullptr;
  }
  shido_WindowRef *ref = new shido_WindowRef{std::make_shared<shido_Window>(handle)};
  shido_Window::getRegistry().reg(handle, ref);
  return ref;
}

shido_WindowRef* shido_Window_get(uint32_t id)
{ return shido_Window::getRegistry().get(SDL_GetWindowFromID(id)); }

int shido_Window_getDisplay(shido_Window *self)
{
  int index = SDL_GetWindowDisplayIndex(self->handle);
  if(index < 0) shido::error(std::string("SDL: ")+SDL_GetError());
  return index;
}
