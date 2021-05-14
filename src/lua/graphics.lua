-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's graphics module.
local API = require("shido.API")
local core = require("shido.core")
local event = require("shido.event")

-- C API
local ffi = require("ffi")
ffi.cdef[[
bool shido_graphics_init();
]]
local L = ffi.load("shido")
-- init module
local graphics = {}
shido.graphics = graphics
-- load handle types
require("shido.graphics.Window")

function graphics.init()
  if not L.shido_graphics_init() then core.error() end
end

function graphics.newWindow(title, w, h)
  local ref = L.shido_Window_new(title, w, h)
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- Default app loop.
function shido.run()
  local evt = ffi.new("SDL_Event[1]")
  local function dispatch(name, ...)
    print("event", name, ...)
    -- dispatch to shido callbacks
    if name and shido[name] then return shido[name](...) end
  end
  -- loop
  local running = true
  while running do
    print(shido.core.getTime())
    while shido.event.poll(evt) do
      if evt[0].type == L.SDL_QUIT then
        running = not not dispatch(shido.event.process(evt[0]))
      else
        dispatch(shido.event.process(evt[0]))
      end
    end
    shido.core.sleep(0.016)
  end
end

return graphics
