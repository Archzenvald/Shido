-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")
local core = require("shido.core")

-- C API
API.defineHandle("View")
ffi.cdef[[
shido_ViewRef* shido_View_new();
]]
local L = ffi.load("shido")

local graphics = shido.graphics

-- Window

function graphics.newView()
  local ref = L.shido_View_new()
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- methods
local View = {}

API.implementHandle("View", View)
