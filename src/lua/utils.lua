-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Framework's utils module.
local core = require("shido.core")

-- init module
local utils = {}
shido.utils = utils

-- Inspect (print) Lua value for debugging.
local function inspect(t, indent, index)
  if not indent then
    io.stdout:write("<inspect>  ")
    indent = 1
  end
  local is_t = type(t) == "table"
  if is_t then -- table
    if index and index[t] then -- detect loop
      io.stdout:write("<loop>\n")
    else
      io.stdout:write("\n")
      -- create sub index
      local sub_index = {}
      for k in pairs(index or {}) do sub_index[k] = true end
      sub_index[t] = true -- mark self
      -- sort keys
      local keys = {}
      for k in pairs(t) do table.insert(keys, k) end
      table.sort(keys, function(a, b) return tostring(a) < tostring(b) end)
      -- recursion
      for _, k in ipairs(keys) do
        io.stdout:write(string.rep("  ", indent))
        io.stdout:write(k.."  ")
        inspect(t[k], indent+1, sub_index)
      end
    end
  else io.stdout:write(tostring(t)) end -- simple values
  if not is_t then io.stdout:write("\n") end
end
utils.inspect = inspect

return utils
