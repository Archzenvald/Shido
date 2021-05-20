-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- API helper.
local ffi = require("ffi")
local L = ffi.load("shido")

local API = {}

ffi.cdef("typedef struct{ void *ptr; } shido_sptr;")
local sptr = ffi.new("shido_sptr[1]")
-- Generate unique key from a pointer.
local function ptr_key(ptr)
  sptr[0].ptr = ptr
  return ffi.string(sptr, ffi.sizeof("shido_sptr"))
end
API.getPtrKey = ptr_key

-- Managed handles.
-- Keep a unique Lua handle for each object.
-- map of object identifier => handle (weak)
local handles = setmetatable({}, {__mode = "v"})

-- Define handle type.
-- shido_T is the C API object handle type.
-- shido_TRef is the C API reference handle type.
-- shido_THandle is the Lua API handle type.
function API.defineHandle(name)
  local def = string.gsub([[
  typedef struct shido_T shido_T;
  typedef struct shido_TRef shido_TRef;
  shido_TRef* shido_TRef_new(shido_TRef*);
  shido_T* shido_TRef_ptr(shido_TRef*);
  void shido_TRef_free(shido_TRef*);

  typedef struct shido_THandle{
    shido_T *obj;
    shido_TRef *ref;
  } shido_THandle;
  ]], "T", name)
  ffi.cdef(def)
  -- set reference metatype
  local ref_mt = {
    __index = {
      __handle_name = name,
      ptr = L["shido_"..name.."Ref_ptr"],
      free = L["shido_"..name.."Ref_free"],
      clone = L["shido_"..name.."Ref_new"]
    }
  }
  ffi.metatype("shido_"..name.."Ref", ref_mt)
end

-- Free handle, further use is undefined behavior.
-- Low-level method to free resources when the GC is not good enough.
function free_handle(self)
  handles[ptr_key(self.obj)] = nil
  self.ref:free()
  self.ref, self.obj = nil, nil
end

-- index: index table for the metatype
function API.implementHandle(name, index)
  index.__free = free_handle
  ffi.metatype("shido_"..name.."Handle", {__index = index})
end

-- Claim a free (memory not already managed) reference.
-- ref: valid reference
function API.claimFreeRef(ref)
  local obj = ref:ptr()
  local key = ptr_key(obj)
  local handle = handles[key]
  if not handle then -- new handle
    local name = ref.__handle_name
    handle = ffi.new("shido_"..name.."Handle")
    handle.obj = obj
    handle.ref = ref
    ffi.gc(handle, function(handle) handle.ref:free() end)
    handles[key] = handle
  else -- already managed, free reference
    ref:free()
  end
  return handle
end

-- Claim an owned reference.
-- ref: valid reference
function API.claimOwnedRef(ref)
  local obj = ref:ptr()
  local key = ptr_key(obj)
  local handle = handles[key]
  if not handle then -- new handle
    local name = ref.__handle_name
    handle = ffi.new("shido_"..name.."Handle")
    handle.obj = obj
    handle.ref = ref:clone()
    ffi.gc(handle, function(handle) handle.ref:free() end)
    handles[key] = handle
  end
  return handle
end

return API
