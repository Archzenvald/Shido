// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_RENDERER
#define HPP_SHIDO_RENDERER

#include "Renderer.h"

#include "../API.hpp"
#include "../graphics.hpp"
#include "Window.hpp"
#include <filament/Renderer.h>

SHIDO_HANDLE_HPP(Renderer)

struct shido_Renderer{
  filament::Renderer *handle;
  shido_SwapChainRef frame_swapchain;
  shido_Renderer(filament::Renderer *_handle): handle(_handle){}
  ~shido_Renderer();
};

#endif
