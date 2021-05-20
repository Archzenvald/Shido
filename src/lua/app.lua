-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's app module.
local core = require("shido.core")
local ffi = require("ffi")
local L = ffi.load("shido")

-- init module
local app = {}
shido.app = app

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

return app
