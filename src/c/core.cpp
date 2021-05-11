// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "core.hpp"

const char* shido_core_getWorkingDirectory()
{
  const static utils::Path path = utils::Path::getCurrentDirectory();
  return path.c_str();
}

const char* shido_core_getExecutableDirectory()
{
  const static utils::Path path = utils::Path::getCurrentExecutable().getParent();
  return path.c_str();
}

bool shido_core_init()
{
  int status = SDL_Init(0);
  if(status != 0)
    std::cerr << "[shido] SDL2 core init failed: " << SDL_GetError() << std::endl;
  return status;
}

void shido_core_quit()
{
  SDL_Quit();
}

void shido_core_sleep(double time)
{
  SDL_Delay((unsigned int)(time*1000));
}
