// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "Renderer.hpp"

SHIDO_HANDLE_CPP(Renderer)

shido_Renderer::~shido_Renderer()
{
  shido::Graphics::get().engine->destroy(handle);
}

shido_RendererRef* shido_Renderer_new()
{
  filament::Renderer *handle = shido::Graphics::get().engine->createRenderer();
  if(!handle){
    shido::error("Filament Renderer creation failed.");
    return nullptr;
  }
  return new shido_RendererRef{std::make_shared<shido_Renderer>(handle)};
}

bool shido_Renderer_beginFrame(shido_Renderer *self, shido_SwapChainRef *swapchain)
{
  // reference swapchain
  self->frame_swapchain = *swapchain;
  return self->handle->beginFrame(swapchain->ref->handle);
}

void shido_Renderer_endFrame(shido_Renderer *self)
{
  // unreference swapchain
  self->frame_swapchain.ref = nullptr;
}
