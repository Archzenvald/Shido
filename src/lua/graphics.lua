-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's graphics module.
local API = require("shido.API")
local core = require("shido.core")
local event = require("shido.event")

-- C API
local ffi = require("ffi")
ffi.cdef[[
typedef struct shido_Display_t{
  const char *name;
  int x, y, w, h;
  int ux, uy, uw, uh;
  bool has_dpi;
  float ddpi, hdpi, vdpi;
} shido_Display_t;

bool shido_graphics_init();
int shido_graphics_getDisplayCount();
void shido_graphics_getDisplay(int index, shido_Display_t *out);
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

-- Get displays infos.
-- return list of displays {}
--- name: can be nil
--- bounds: {.x, .y, .w, .h}
--- usable_boundes: {.x, .y, .w, .h}
--- dpi: can be nil, {}
---- d: diagonal DPI
---- h: horizontal DPI
---- v: vertical DPI
function graphics.getDisplays()
  local dispdata = ffi.new("shido_Display_t[1]")
  local count = L.shido_graphics_getDisplayCount();
  local displays = {}
  for i=0,count-1 do
    L.shido_graphics_getDisplay(i, dispdata)
    local display = {}
    if dispdata[0].name ~= nil then display.name = ffi.string(dispdata[0].name) end
    display.bounds = {
      x = dispdata[0].x,
      y = dispdata[0].y,
      w = dispdata[0].w,
      h = dispdata[0].h
    }
    display.usable_bounds = {
      ux = dispdata[0].ux,
      uy = dispdata[0].uy,
      uw = dispdata[0].uw,
      uh = dispdata[0].uh
    }
    if dispdata[0].has_dpi then
      display.dpi = {
        d = dispdata[0].ddpi,
        h = dispdata[0].hdpi,
        v = dispdata[0].vdpi
      }
    end
    table.insert(displays, display)
  end
  return displays
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
