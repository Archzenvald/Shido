print(shido.core.getExecutableDirectory())
print(shido.core.getWorkingDirectory())

local view = shido.graphics.newView()

function shido.keyPressed(k, scancode, is_repeat, window)
end

function shido.tick(dt)
  print("tick", dt, "tickrate", shido.app.tickrate, "tickload", shido.app.tickload*100)
  print("framerate", shido.app.framerate)
end

function shido.render(renderer)
  renderer:render(view)
end

function shido.quit() print("quitting") end
