-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's app module.
local core = require("shido.core")
local ffi = require("ffi")
local L = ffi.load("shido")

-- init module
local app = {}
shido.app = app

function app.init()
  app.window = shido.graphics.newWindow("shido", 800, 600)
  app.swapchain = shido.graphics.newSwapChain(shido.app.window)
  app.renderer = shido.graphics.newRenderer()
  local tick_period
  function app.setTargetTickrate(tickrate) tick_period = 1/tickrate end
  app.setTargetTickrate(60)
  -- stats
  app.tickrate = 0
  app.framerate = 0
  app.tickload = 0 -- non-sleeping fraction of the tick period

  -- Define default app loop.
  function shido.run()
    local evt = ffi.new("SDL_Event[1]")
    local function dispatch(name, ...)
      print("event", name, ...)
      -- dispatch to shido callbacks
      if name and shido[name] then return shido[name](...) end
    end
    -- loop
    local last_time = shido.core.getTime()
    local stats_time, tick_count, frame_count = last_time, 0, 0
    local running = true
    while running do
      local start_time = shido.core.getTime()
      -- compute stats
      local stats_dt = start_time-stats_time
      if stats_dt >= 1 then
        app.tickrate = tick_count/stats_dt
        app.framerate = frame_count/stats_dt
        stats_time, tick_count, frame_count = start_time, 0, 0
      end
      -- handle events
      while shido.event.poll(evt) do
        if evt[0].type == L.SDL_QUIT then
          running = not not dispatch(shido.event.process(evt[0]))
        else
          dispatch(shido.event.process(evt[0]))
        end
      end
      -- tick
      if shido.tick then shido.tick(start_time-last_time) end
      tick_count = tick_count+1
      -- render
      if shido.render then
        if app.renderer:beginFrame(app.swapchain) then
          shido.render(app.renderer) -- must render something or undefined behavior
          app.renderer:endFrame()
          frame_count = frame_count+1
        end
      end
      -- sleep
      local it_duration = shido.core.getTime()-start_time
      app.tickload = it_duration/tick_period
      if it_duration < tick_period then shido.core.sleep(tick_period-it_duration) end
      -- next
      last_time = start_time
    end
  end
end

return app
