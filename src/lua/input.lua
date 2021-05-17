-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's input module.
local API = require("shido.API")
local core = require("shido.core")

-- C API
local ffi = require("ffi")
ffi.cdef[[
bool shido_input_init();
]]
local L = ffi.load("shido")
-- init module
local input = {}
shido.input = input

function input.init()
  if not L.shido_input_init() then core.error() end
end

return input
