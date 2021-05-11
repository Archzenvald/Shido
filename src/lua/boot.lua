-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

-- Function to boot the shido environment.
-- ...: program arguments
return function(...)
  -- load modules
  require("shido.core")
  require("shido.graphics")
  -- init modules
  shido.core.init()
  shido.graphics.init()
  -- run main
  local f, err = loadfile("main.lua")
  if not f then error(err) end
  f(...)
  -- run
  shido.run()
  -- quit
  shido.core.quit()
end
