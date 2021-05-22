-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's input module.
local bit = require("bit")
local API = require("shido.API")
local core = require("shido.core")
local SDL = require("shido.SDL")

-- C API
local ffi = require("ffi")
ffi.cdef[[
bool shido_input_init();
const Uint8* shido_input_getKeyboardState();
SDL_Keymod shido_input_getKeyboardMod();
SDL_Keycode shido_input_getKeyFromScancode(SDL_Scancode scancode);
SDL_Scancode shido_input_getScancodeFromKey(SDL_Keycode keycode);
bool shido_input_hasScreenKeyboard();
bool shido_input_isTextInputActive();
void shido_input_setTextInputRect(int x, int y, int w, int h);
void shido_input_startTextInput();
void shido_input_stopTextInput();
void shido_input_getMousePosition(int out[2]);
Uint32 shido_input_getMouseState();
void shido_input_warpMouse(int x, int y, shido_Window *window);
bool shido_input_setRelativeMouseMode(bool enable);
bool shido_input_getRelativeMouseMode();
]]
local L = ffi.load("shido")
-- init module
local input = {}
shido.input = input

local keyboard_state
function input.init()
  if not L.shido_input_init() then core.error() end
  keyboard_state = L.shido_input_getKeyboardState();
end

-- Keyboard.
function input.getKeyFromScancode(scancode)
  scancode = SDL.scancode_map[scancode]
  local keycode = L.shido_input_getKeyFromScancode(scancode)
  return SDL.keycode_map[keycode]
end
function input.getScancodeFromKey(keycode)
  keycode = SDL.keycode_map[keycode]
  local scancode = tonumber(L.shido_input_getScancodeFromKey(keycode))
  return SDL.scancode_map[scancode]
end
function input.isScancodeDown(scancode)
  scancode = SDL.scancode_map[scancode]
  return scancode and keyboard_state[scancode] == 1
end
function input.isKeyDown(keycode)
  return input.isScancodeDown(input.getScancodeFromKey(keycode))
end
function input.hasScreenKeyboard() return L.shido_input_hasScreenKeyboard() end
function input.isTextInputActive() return L.shido_input_isTextInputActive() end
function input.setTextInput(enable, x, y, w, h)
  if enable then
    L.shido_input_startTextInput()
    if x then L.shido_input_setTextInputRect(x, y or 0, w or 0, h or 0) end
  else
    L.shido_input_stopTextInput()
  end
end
function input.hasKeyMod(keymod)
  keymod = SDL.keymod_map[keymod]
  if keymod then
    local state = tonumber(L.shido_input_getKeyboardMod());
    return bit.band(state, keymod) ~= 0
  end
end

-- Mouse.
function input.getMousePosition()
  local out = ffi.new("int[2]")
  L.shido_input_getMousePosition(out)
  return out[0], out[1]
end
function input.isMouseDown(button)
  local id = SDL.mouse_button_map[button]
  if id then
    local state = L.shido_input_getMouseState()
    return bit.band(state, bit.lshift(1, id-1)) ~= 0
  end
end
-- Warp mouse into a window.
-- x,y: position
-- window: (optional) target window
function input.warpMouse(x, y, window)
  L.shido_input_warpMouse(x, y, window and window.obj or nil)
end
-- Enable/disable relative mouse mode.
-- return true or (false, err) on failure
function input.setRelativeMouseMode(enable)
  local ok = L.shido_input_setRelativeMouseMode(enable)
  if not ok then return ok, core.getError() end
  return ok
end
-- Get relative mouse mode state.
-- return true if enabled
function input.getRelativeMouseMode() return L.shido_input_getRelativeMouseMode() end

return input
