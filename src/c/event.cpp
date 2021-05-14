// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "event.hpp"

bool shido_event_init()
{
  bool ok = (SDL_InitSubSystem(SDL_INIT_EVENTS) == 0);
  if(!ok)
    shido::error(std::string("SDL event init failed: ")+SDL_GetError());
  return ok;
}

bool shido_event_push(SDL_Event *event)
{
  bool ok = (SDL_PushEvent(event) >= 0);
  if(!ok)
    shido::error(std::string("SDL event push failed: ")+SDL_GetError());
  return ok;
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
