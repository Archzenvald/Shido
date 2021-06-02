-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

local ffi = require("ffi")
local API = require("shido.API")
local core = require("shido.core")

-- C API
API.defineHandle("Scene")
ffi.cdef[[
shido_SceneRef* shido_Scene_new();
]]
local L = ffi.load("shido")

local graphics = shido.graphics

-- Window

function graphics.newScene()
  local ref = L.shido_Scene_new()
  if ref == nil then core.error() end
  return API.claimFreeRef(ref)
end

-- methods
local Scene = {}

API.implementHandle("Scene", Scene)
