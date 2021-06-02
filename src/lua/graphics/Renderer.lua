-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")
local core = require("shido.core")
require("shido.graphics.View")

-- C API
API.defineHandle("Renderer")
ffi.cdef[[
shido_RendererRef* shido_Renderer_new();
bool shido_Renderer_beginFrame(shido_Renderer *self, shido_SwapChainRef *swapchain);
void shido_Renderer_render(shido_Renderer *self, shido_View *view);
void shido_Renderer_endFrame(shido_Renderer *self);
]]
local L = ffi.load("shido")

local graphics = shido.graphics

-- Window

function graphics.newRenderer()
  local ref = L.shido_Renderer_new()
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- methods
local Renderer = {}

function Renderer:beginFrame(swapchain)
  return L.shido_Renderer_beginFrame(self.obj, swapchain.ref)
end
function Renderer:render(view) L.shido_Renderer_render(self.obj, view.obj) end
function Renderer:endFrame() L.shido_Renderer_endFrame(self.obj) end

API.implementHandle("Renderer", Renderer)
