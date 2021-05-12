// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "event.hpp"

bool shido_event_init()
{
  int status = SDL_InitSubSystem(SDL_INIT_EVENTS);
  if(status != 0)
    std::cerr << "[shido] SDL2 event init failed: " << SDL_GetError() << std::endl;
  return status;
}

bool shido_event_push(SDL_Event *event)
{
  int status = SDL_PushEvent(event);
  if(status < 0)
    std::cerr << "[shido] SDL2 event push failed: " << SDL_GetError() << std::endl;
  return status >= 0;
}

bool shido_event_poll(SDL_Event *event)
{
  return SDL_PollEvent(event);
}

void shido_event_cleanup(SDL_Event *_event)
{
  SDL_Event &event = *_event;
  switch(event.type){
    case SDL_DROPFILE:
    case SDL_DROPTEXT:
      if(event.drop.file){
        SDL_free(event.drop.file);
        event.drop.file = nullptr;
      }
    break;
  }
}
