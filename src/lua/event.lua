-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's event module.

local core = require("shido.core")
local SDL = require("shido.SDL")

-- C API
local ffi = require("ffi")
ffi.cdef[[
bool shido_event_init();
bool shido_event_push(SDL_Event *event);
bool shido_event_poll(SDL_Event *event);
void shido_event_cleanup(SDL_Event *event);
]]
local L = ffi.load("shido")
-- init module
local event = {}
shido.event = event

function event.init()
  if not L.shido_event_init() then core.error() end
end
function event.push(e)
  if not L.shido_event_push(e) then core.error() end
end
function event.poll(e) return L.shido_event_poll(e) end
function event.cleanup(e) L.shido_event_cleanup(e) end

-- SDL_Event processors, map of event type => function.
local processors = {}
-- Process SDL_Event data and cleanup the structure.
-- e: SDL_Event&
-- return (name, args...) or nil if invalid
function event.process(e)
  local p = processors[e.type]
  if p then return p(e) end
end

processors[L.SDL_QUIT] = function(e) return "quit" end

-- Window events.
-- map of window event type => function
do
  local subprocs = {}
  processors[L.SDL_WINDOWEVENT] = function(e)
    local p = subprocs[e.window.event]
    if p then return p(e) end
  end
  subprocs[L.SDL_WINDOWEVENT_SHOWN] = function(e)
    return "windowVisible", true, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_HIDDEN] = function(e)
    return "windowVisible", false, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_MOVED] = function(e)
    return "windowMoved", e.window.data1, e.window.data2, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_RESIZED] = function(e)
    return "windowResized", e.window.data1, e.window.data2, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_MAXIMIZED] = function(e)
    return "windowMaximized", e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_MINIMIZED] = function(e)
    return "windowMinimized", e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_RESTORED] = function(e)
    return "windowRestored", e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_ENTER] = function(e)
    return "windowMouseFocus", true, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_LEAVE] = function(e)
    return "windowMouseFocus", false, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_FOCUS_GAINED] = function(e)
    return "windowFocus", true, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_FOCUS_LOST] = function(e)
    return "windowFocus", false, e.window.windowID
  end
  subprocs[L.SDL_WINDOWEVENT_CLOSE] = function(e)
    return "windowClosed", e.window.windowID
  end
end

-- Keyboard events.
local function p_keyboard(e)
  local name = (e.key.state == 1 and "keyPressed" or "keyReleased")
  local is_repeat = (e.key["repeat"] ~= 0)
  local keycode = SDL.keycode_map[e.key.keysym.sym]
  local scancode = SDL.scancode_map[tonumber(e.key.keysym.scancode)]
  return name, keycode, scancode, is_repeat, e.key.windowID
end
processors[L.SDL_KEYDOWN] = p_keyboard
processors[L.SDL_KEYUP] = p_keyboard

return event
