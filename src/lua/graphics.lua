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
int shido_graphics_getDisplayModeCount(int index);
bool shido_graphics_getDisplayMode(int index, int mode_index, SDL_DisplayMode *out);
]]
local L = ffi.load("shido")
-- init module
local graphics = {}
shido.graphics = graphics
-- load handle types
require("shido.graphics.Window")
require("shido.graphics.Renderer")
require("shido.graphics.View")

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
  local out = ffi.new("shido_Display_t[1]")
  local count = L.shido_graphics_getDisplayCount()
  local displays = {}
  for i=0, count-1 do
    L.shido_graphics_getDisplay(i, out)
    local display = {}
    if out[0].name ~= nil then display.name = ffi.string(out[0].name) end
    display.bounds = {
      x = out[0].x,
      y = out[0].y,
      w = out[0].w,
      h = out[0].h
    }
    display.usable_bounds = {
      ux = out[0].ux,
      uy = out[0].uy,
      uw = out[0].uw,
      uh = out[0].uh
    }
    if out[0].has_dpi then
      display.dpi = {
        d = out[0].ddpi,
        h = out[0].hdpi,
        v = out[0].vdpi
      }
    end
    table.insert(displays, display)
  end
  return displays
end

-- Get display mode.
-- index, mode_index: 0-based
local function getDisplayMode(index, mode_index)
  local out = ffi.new("SDL_DisplayMode[1]")
  if L.shido_graphics_getDisplayMode(index, mode_index, out) then
    return {
      w = out[0].w,
      h = out[0].h,
      rate = out[0].refresh_rate,
      raw = out
    }
  end
end

-- index: 1-based, as returned by getDisplays()
-- return list (+.desktop) of modes {}
--- w,h: dimensions
--- rate: refresh rate
--- raw: SDL_DisplayMode[1]
function graphics.getDisplayModes(index)
  local modes = {}
  -- available display modes
  local count = L.shido_graphics_getDisplayModeCount(index-1)
  for i=0, count-1 do table.insert(modes, getDisplayMode(index-1, i)) end
  -- desktop mode
  modes.desktop = getDisplayMode(index-1, -1)
  return modes
end

require("shido.deferred").loaded("shido.graphics", graphics)
return graphics
