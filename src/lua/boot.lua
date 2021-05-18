-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Function to boot the shido environment.
-- ...: program arguments
return function(...)
  -- load modules
  require("shido.core")
  require("shido.event")
  require("shido.graphics")
  require("shido.input")
  require("shido.utils")
  -- init modules
  shido.core.init()
  shido.event.init()
  shido.graphics.init()
  shido.input.init()
  -- init basic resources
  shido.graphics.window = shido.graphics.newWindow("shido", 800, 600)
  -- run main
  local f, err = loadfile("main.lua")
  if not f then error(err) end
  f(...)
  -- run
  if shido.run then shido.run() end
end
