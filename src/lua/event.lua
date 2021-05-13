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

function event.init() return L.shido_event_init() end
function event.push(e) return L.shido_event_push(e) end
function event.poll(e) return L.shido_event_poll(e) end
function event.cleanup(e) L.shido_event_cleanup(e) end

-- SDL_Event processors, map of event type => function.
local processors = {}
-- Process SDL_Event data and cleanup the structure.
-- e: SDL_Event&
-- return (name, args...) or nil if invalid
function event.process(e)
  local processor = processors[e.type]
  return processor and processor(e)
end

processors[L.SDL_QUIT] = function(e) return "quit" end

return event
