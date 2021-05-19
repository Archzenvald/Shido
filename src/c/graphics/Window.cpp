// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "Window.hpp"

SHIDO_HANDLE_CPP(Window)

shido_Window::~shido_Window()
{
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
  return new shido_WindowRef{std::make_shared<shido_Window>(handle)};
}

int shido_Window_getDisplay(shido_Window *self)
{
  int index = SDL_GetWindowDisplayIndex(self->handle);
  if(index < 0) shido::error(std::string("SDL: ")+SDL_GetError());
  return index;
}
