// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_WINDOW
#define HPP_SHIDO_WINDOW

#include "Window.h"
#include "../API.hpp"
#include "../core.hpp"
#include "../graphics.hpp"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_syswm.h>
#include <filament/SwapChain.h>

SHIDO_HANDLE_HPP(Window)
SHIDO_HANDLE_HPP(SwapChain)

struct shido_Window{
  SDL_Window *handle;
  shido_Window(SDL_Window *_handle): handle(_handle){}
  ~shido_Window();

  static shido::Registry<SDL_Window*, shido_WindowRef>& getRegistry();
};

struct shido_SwapChain{
  filament::SwapChain *handle;
  shido_WindowRef window;

  shido_SwapChain(shido_WindowRef *_window, filament::SwapChain *_handle):
    window(*_window), handle(_handle){}
  ~shido_SwapChain();
};

#endif
