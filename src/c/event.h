// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_EVENT
#define H_SHIDO_EVENT

#include <SDL2/SDL_events.h>

#ifdef __cplusplus
extern "C"{
#endif

#include "API.h"

SHIDO_API bool shido_event_init();
SHIDO_API bool shido_event_push(SDL_Event *event);
SHIDO_API bool shido_event_poll(SDL_Event *event);
SHIDO_API void shido_event_cleanup(SDL_Event *event);

#ifdef __cplusplus
}
#endif

#endif
