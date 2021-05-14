-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")

-- C API
API.defineHandle("Window")
ffi.cdef[[
shido_WindowRef* shido_Window_new(const char *title, int w, int h);
]]
local L = ffi.load("shido")

local Window = {}

API.implementHandle("Window", Window)
