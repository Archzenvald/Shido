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

return input
