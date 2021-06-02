-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")
local core = require("shido.core")

-- C API
API.defineHandle("Entity")
ffi.cdef[[
shido_EntityRef* shido_Entity_new();
]]
local L = ffi.load("shido")

local graphics = shido.graphics

-- Window

function graphics.newEntity()
  local ref = L.shido_Entity_new()
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- methods
local Entity = {}

API.implementHandle("Entity", Entity)
