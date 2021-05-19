// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "graphics.hpp"

bool shido_graphics_init()
{
  bool ok = (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0);
  if(!ok)
    shido::error(std::string("SDL: ")+SDL_GetError());
  return ok;
}

int shido_graphics_getDisplayCount(){ return SDL_GetNumVideoDisplays(); }

void shido_graphics_getDisplay(int index, shido_Display_t *out)
{
  SDL_Rect rect;
  *out = shido_Display_t{}; // init
  // name
  out->name = SDL_GetDisplayName(index);
  if(out->name == nullptr)
    shido::warning(std::string("SDL: ")+SDL_GetError());
  // bounds
  if(SDL_GetDisplayBounds(index, &rect) == 0){
    out->x = rect.x;
    out->y = rect.y;
    out->w = rect.w;
    out->h = rect.h;
  }
  else
    shido::warning(std::string("SDL: ")+SDL_GetError());
  // usable bounds
  if(SDL_GetDisplayUsableBounds(index, &rect) == 0){
    out->ux = rect.x;
    out->uy = rect.y;
    out->uw = rect.w;
    out->uh = rect.h;
  }
  else
    shido::warning(std::string("SDL: ")+SDL_GetError());
  // dpi
  out->has_dpi = (SDL_GetDisplayDPI(index, &out->ddpi, &out->hdpi, &out->vdpi) == 0);
}

int shido_graphics_getDisplayModeCount(int index)
{ return SDL_GetNumDisplayModes(index); }

bool shido_graphics_getDisplayMode(int index, int mode_index, SDL_DisplayMode *out)
{
  bool ok;
  if(mode_index < 0)
    ok = (SDL_GetDesktopDisplayMode(index, out) == 0);
  else
    ok = (SDL_GetDisplayMode(index, mode_index, out) == 0);
  if(!ok)
    shido::warning(std::string("SDL: ")+SDL_GetError());
  return ok;
}
