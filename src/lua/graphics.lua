-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local core = require("shido.core")

-- C API
local ffi = require("ffi")
ffi.cdef[[
bool shido_graphics_init();
]]
local L = ffi.load("shido")
-- init module
local graphics = {}
shido.graphics = graphics

function graphics.init() return L.shido_graphics_init() end

-- Default app loop.
function shido.run()
  local running = true
  while running do
    print(shido.core.getTime())
    shido.core.sleep(0.016)
  end
end

return graphics
