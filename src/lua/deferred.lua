-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Deferred load helper.
-- Can be used to handle circular dependencies.
local deferred = {}

local resources = {} -- map of identifiers => {.listeners, .data}

-- callback(data): called when the identifier is loaded
function deferred.postLoad(identifier, callback)
  -- init resource
  local resource = resources[identifier]
  if not resource then
    resource = {listeners = {}}
    resources[identifier] = resource
  end
  if not resource.listeners then callback(resource.data) -- already loaded
  else resource.listeners[callback] = true end -- waiting
end

-- data: (optional)
function deferred.loaded(identifier, data)
  -- init resource
  local resource = resources[identifier]
  if not resource then
    resource = {}
    resources[identifier] = resource
  end
  if resource.listeners then -- trigger callbacks
    for callback in pairs(resource.listeners) do callback(data) end
    resource.listeners = nil
    resource.data = data
  end
end

return deferred
