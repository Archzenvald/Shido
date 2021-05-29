-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")
local core = require("shido.core")

-- C API
API.defineHandle("Window")
API.defineHandle("SwapChain")
ffi.cdef[[
shido_WindowRef* shido_Window_new(const char *title, int w, int h);
shido_WindowRef* shido_Window_get(uint32_t id);
int shido_Window_getDisplayIndex(shido_Window *self);
bool shido_Window_hasInputGrab(shido_Window *self);
void shido_Window_getMinimumSize(shido_Window *self, int out[2]);
void shido_Window_getMaximumSize(shido_Window *self, int out[2]);
float shido_Window_getOpacity(shido_Window *self);
void shido_Window_getPosition(shido_Window *self, int out[2]);
void shido_Window_getSize(shido_Window *self, int out[2]);
const char* shido_Window_getTitle(shido_Window *self);
void shido_Window_hide(shido_Window *self);
void shido_Window_show(shido_Window *self);
void shido_Window_maximize(shido_Window *self);
void shido_Window_minimize(shido_Window *self);
void shido_Window_raise(shido_Window *self);
void shido_Window_restore(shido_Window *self);
bool shido_Window_setFullscreen(shido_Window *self, bool enable, bool desktop);
bool shido_Window_setDisplayMode(shido_Window *self, const SDL_DisplayMode *mode);
void shido_Window_setInputGrab(shido_Window *self, bool enable);
void shido_Window_setResizable(shido_Window *self, bool flag);
void shido_Window_setBordered(shido_Window *self, bool flag);
void shido_Window_setOpacity(shido_Window *self, float opacity);
void shido_Window_setMinimumSize(shido_Window *self, int w, int h);
void shido_Window_setMaximumSize(shido_Window *self, int w, int h);
void shido_Window_setSize(shido_Window *self, int w, int h);
void shido_Window_setPosition(shido_Window *self, int x, int y);
void shido_Window_setTitle(shido_Window *self, const char *title);
void shido_Window_getFullscreen(shido_Window *self, bool out[2]);
bool shido_Window_isVisible(shido_Window *self);
bool shido_Window_isResizable(shido_Window *self);
bool shido_Window_isBordered(shido_Window *self);
bool shido_Window_isMaximized(shido_Window *self);
bool shido_Window_isMinimized(shido_Window *self);
bool shido_Window_hasFocus(shido_Window *self);
bool shido_Window_hasMouseFocus(shido_Window *self);

shido_SwapChainRef* shido_SwapChain_new(shido_WindowRef *window);
]]
local L = ffi.load("shido")

local graphics = shido.graphics

-- Window

function graphics.newWindow(title, w, h)
  local ref = L.shido_Window_new(title, w, h)
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- Get window from id.
function graphics.getWindow(id)
  local ref = L.shido_Window_get(id)
  if ref ~= nil then return API.claimFreeRef(ref) end
end

-- methods
local Window = {}

-- Get window display index.
-- return 1-based index
function Window:getDisplayIndex()
  local index = L.shido_Window_getDisplayIndex(self.obj)
  if index < 0 then core.error() end
  return index+1
end
function Window:hasInputGrab() return L.shido_Window_hasInputGrab(self.obj) end

function Window:getMinimumSize()
  local out = ffi.new("int[2]")
  L.shido_Window_getMinimumSize(self.obj, out)
  return out[0], out[1]
end
function Window:getMaximumSize()
  local out = ffi.new("int[2]")
  L.shido_Window_getMaximumSize(self.obj, out)
  return out[0], out[1]
end
function Window:getOpacity() return L.shido_Window_getOpacity(self.obj) end
function Window:getPosition()
  local out = ffi.new("int[2]")
  L.shido_Window_getPosition(self.obj, out)
  return out[0], out[1]
end
function Window:getSize()
  local out = ffi.new("int[2]")
  L.shido_Window_getSize(self.obj, out)
  return out[0], out[1]
end
function Window:getTitle() return ffi.string(L.shido_Window_getTitle(self.obj)) end
function Window:hide() L.shido_Window_hide(self.obj) end
function Window:show() L.shido_Window_show(self.obj) end
function Window:maximize() L.shido_Window_maximize(self.obj) end
function Window:minimize() L.shido_Window_minimize(self.obj) end
function Window:raise() L.shido_Window_raise(self.obj) end
function Window:restore() L.shido_Window_restore(self.obj) end
-- Set fullscreen state.
-- desktop: (optional) true for non-exclusive desktop/windowed fullscreen
-- return true or (false, err) on failure
function Window:setFullscreen(enable, desktop)
  local ok = L.shido_Window_setFullscreen(self.obj, enable, not not desktop)
  if not ok then return ok, core.getError() end
  return ok
end
-- Set fullscreen display mode.
-- mode: as returned by graphics.getDisplayMode()
-- return true or (false, err) on failure
function Window:setDisplayMode(mode)
  local ok = L.shido_Window_setDisplayMode(self.obj, mode.raw)
  if not ok then return ok, core.getError() end
  return ok
end

function Window:setInputGrab(enable) L.shido_Window_setInputGrab(self.obj, enable) end
function Window:setResizable(flag) L.shido_Window_setResizable(self.obj, flag) end
function Window:setBordered(flag) L.shido_Window_setBordered(self.obj, flag) end
function Window:setOpacity(opacity) L.shido_Window_setOpacity(self.obj, opacity) end
function Window:setMinimumSize(w, h) L.shido_Window_setMinimumSize(self.obj, w, h) end
function Window:setMaximumSize(w, h) L.shido_Window_setMaximumSize(self.obj, w, h) end
function Window:setSize(w, h) L.shido_Window_setSize(self.obj, w, h) end
function Window:setPosition(x, y) L.shido_Window_setPosition(self.obj, x, y) end
function Window:setTitle(title) L.shido_Window_setTitle(self.obj, title) end

function Window:getFullscreen()
  local out = ffi.new("bool[2]")
  L.shido_Window_getFullscreen(self.obj, out)
  return out[0], out[1]
end
function Window:isVisible() return L.shido_Window_isVisible(self.obj) end
function Window:isResizable() return L.shido_Window_isResizable(self.obj) end
function Window:isBordered() return L.shido_Window_isBordered(self.obj) end
function Window:isMaximized() return L.shido_Window_isMaximized(self.obj) end
function Window:isMinimized() return L.shido_Window_isMinimized(self.obj) end
function Window:hasFocus() return L.shido_Window_hasFocus(self.obj) end
function Window:hasMouseFocus() return L.shido_Window_hasMouseFocus(self.obj) end

API.implementHandle("Window", Window)

-- SwapChain

function graphics.newSwapChain(window)
  local ref = L.shido_SwapChain_new(window.ref)
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- methods
local SwapChain = {}

API.implementHandle("SwapChain", SwapChain)
