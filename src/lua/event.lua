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
-- function(e): should return (name, ...) or nil
local processors = {}
-- Process SDL_Event data and cleanup the structure.
-- e: SDL_Event&
-- return (name, args...) or nil if invalid
function event.process(e)
  local p = processors[e.type]
  if p then return p(e) end
end

processors[L.SDL_QUIT] = function(e) return "quit" end

-- Drop events.
do
  local drop_files = {} -- map of window id => list of files
  processors[L.SDL_DROPBEGIN] = function(e) drop_files[e.drop.windowID] = {} end
  processors[L.SDL_DROPCOMPLETE] = function(e)
    local wid = e.drop.windowID
    local files = drop_files[wid]
    drop_files[wid] = nil
    return "filesDropped", files, wid
  end
  processors[L.SDL_DROPFILE] = function(e)
    local file = ffi.string(e.drop.file)
    local wid = e.drop.windowID
    L.shido_event_cleanup(e)
    local files = drop_files[wid]
    if files then table.insert(files, file) -- add to drop's batch
    else return "filesDropped", {file}, wid end -- single file
  end
  processors[L.SDL_DROPTEXT] = function(e)
    local text = ffi.string(e.drop.file)
    local wid = e.drop.windowID
    L.shido_event_cleanup(e)
    return "textDropped", text, wid
  end
end

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
processors[L.SDL_TEXTEDITING] = function(e)
  return "textEditing", ffi.string(e.edit.text), e.edit.start, e.edit.length, e.edit.windowID
end
processors[L.SDL_TEXTINPUT] = function(e)
  return "textInput", ffi.string(e.text.text), e.text.windowID
end

-- Mouse events.
processors[L.SDL_MOUSEMOTION] = function(e)
  return "mouseMoved", e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel, e.motion.windowID
end
local function p_mouse_button(e)
  local name = (e.button.state == 1 and "mousePressed" or "mouseReleased")
  local button = SDL.mouse_button_map[e.button.button]
  return name, e.button.x, e.button.y, button, e.button.clicks, e.button.windowID
end
processors[L.SDL_MOUSEBUTTONDOWN] = p_mouse_button
processors[L.SDL_MOUSEBUTTONUP] = p_mouse_button
processors[L.SDL_MOUSEWHEEL] = function(e)
  return "mouseWheel", e.wheel.x, e.wheel.y, e.wheel.windowID
end

return event
