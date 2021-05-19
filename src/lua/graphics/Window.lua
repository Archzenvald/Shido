-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")
local core = require("shido.core")

-- C API
API.defineHandle("Window")
ffi.cdef[[
shido_WindowRef* shido_Window_new(const char *title, int w, int h);
int shido_Window_getDisplay(shido_Window *self);
]]
local L = ffi.load("shido")

local Window = {}

-- Get window display.
-- return 1-based index
function Window:getDisplay()
  local index = L.shido_Window_getDisplay(self.obj)
  if index < 0 then core.error() end
  return index+1
end

API.implementHandle("Window", Window)
