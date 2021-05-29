// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_RENDERER
#define H_SHIDO_RENDERER

#ifdef __cplusplus
extern "C"{
#endif

#include "../API.h"
#include "Window.h"

SHIDO_HANDLE_H(Renderer)

// Create renderer.
// return new reference or NULL on failure (error)
SHIDO_API shido_RendererRef* shido_Renderer_new();
SHIDO_API bool shido_Renderer_beginFrame(shido_Renderer *self, shido_SwapChainRef *swapchain);
SHIDO_API void shido_Renderer_endFrame(shido_Renderer *self);

#ifdef __cplusplus
}
#endif

#endif
