-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")
local core = require("shido.core")

-- C API
API.defineHandle("Window")
ffi.cdef[[
shido_WindowRef* shido_Window_new(const char *title, int w, int h);
shido_WindowRef* shido_Window_get(uint32_t id);
int shido_Window_getDisplay(shido_Window *self);
]]
local L = ffi.load("shido")

local graphics = shido.graphics

function graphics.newWindow(title, w, h)
  local ref = L.shido_Window_new(title, w, h)
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- Get window from id.
function graphics.getWindow(id)
  local ref = L.shido_Window_get(id)
  if ref ~= nil then return API.claimFreeRef(ref) end
end

-- Methods.
local Window = {}

-- Get window display.
-- return 1-based index
function Window:getDisplay()
  local index = L.shido_Window_getDisplay(self.obj)
  if index < 0 then core.error() end
  return index+1
end

API.implementHandle("Window", Window)
