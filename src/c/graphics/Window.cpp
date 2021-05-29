// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "Window.hpp"

SHIDO_HANDLE_CPP(Window)
SHIDO_HANDLE_CPP(SwapChain)

// Window

shido::Registry<SDL_Window*, shido_WindowRef>& shido_Window::getRegistry()
{
  static shido::Registry<SDL_Window*, shido_WindowRef> registry;
  return registry;
}

shido_Window::~shido_Window()
{
  shido_Window::getRegistry().unreg(handle);
  SDL_DestroyWindow(handle);
}

shido_WindowRef* shido_Window_new(const char *title, int w, int h)
{
  SDL_Window *handle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
  if(!handle){
    shido::error(std::string("SDL: ")+SDL_GetError());
    return nullptr;
  }
  shido_WindowRef *ref = new shido_WindowRef{std::make_shared<shido_Window>(handle)};
  shido_Window::getRegistry().reg(handle, ref);
  return ref;
}

shido_WindowRef* shido_Window_get(uint32_t id)
{ return shido_Window::getRegistry().get(SDL_GetWindowFromID(id)); }

int shido_Window_getDisplayIndex(shido_Window *self)
{
  int index = SDL_GetWindowDisplayIndex(self->handle);
  if(index < 0) shido::error(std::string("SDL: ")+SDL_GetError());
  return index;
}

bool shido_Window_hasInputGrab(shido_Window *self)
{ return SDL_GetWindowGrab(self->handle); }

void shido_Window_getMinimumSize(shido_Window *self, int out[2])
{ SDL_GetWindowMinimumSize(self->handle, out, out+1); }

void shido_Window_getMaximumSize(shido_Window *self, int out[2])
{ SDL_GetWindowMaximumSize(self->handle, out, out+1); }

float shido_Window_getOpacity(shido_Window *self)
{
  float out = 1.0f;
  SDL_GetWindowOpacity(self->handle, &out);
  return out;
}

void shido_Window_getPosition(shido_Window *self, int out[2])
{ SDL_GetWindowPosition(self->handle, out, out+1); }

void shido_Window_getSize(shido_Window *self, int out[2])
{ SDL_GetWindowSize(self->handle, out, out+1); }

const char* shido_Window_getTitle(shido_Window *self)
{ return SDL_GetWindowTitle(self->handle); }

void shido_Window_hide(shido_Window *self){ SDL_HideWindow(self->handle); }
void shido_Window_show(shido_Window *self){ SDL_ShowWindow(self->handle); }
void shido_Window_maximize(shido_Window *self){ SDL_MaximizeWindow(self->handle); }
void shido_Window_minimize(shido_Window *self){ SDL_MinimizeWindow(self->handle); }
void shido_Window_raise(shido_Window *self){ SDL_RaiseWindow(self->handle); }
void shido_Window_restore(shido_Window *self){ SDL_RestoreWindow(self->handle); }

bool shido_Window_setFullscreen(shido_Window *self, bool enable, bool desktop)
{
  Uint32 flags = 0;
  if(enable)
    flags = (desktop ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_FULLSCREEN);
  bool ok = (SDL_SetWindowFullscreen(self->handle, flags) == 0);
  if(!ok)
    shido::error(std::string("SDL: ")+SDL_GetError());
  return ok;
}

bool shido_Window_setDisplayMode(shido_Window *self, const SDL_DisplayMode *mode)
{
  bool ok = (SDL_SetWindowDisplayMode(self->handle, mode) == 0);
  if(!ok)
    shido::error(std::string("SDL: ")+SDL_GetError());
  return ok;
}

void shido_Window_setInputGrab(shido_Window *self, bool enable)
{ SDL_SetWindowGrab(self->handle, enable ? SDL_TRUE : SDL_FALSE); }
void shido_Window_setResizable(shido_Window *self, bool flag)
{ SDL_SetWindowResizable(self->handle, flag ? SDL_TRUE : SDL_FALSE); }
void shido_Window_setBordered(shido_Window *self, bool flag)
{ SDL_SetWindowBordered(self->handle, flag ? SDL_TRUE : SDL_FALSE); }
void shido_Window_setOpacity(shido_Window *self, float opacity)
{ SDL_SetWindowOpacity(self->handle, opacity); }
void shido_Window_setMinimumSize(shido_Window *self, int w, int h)
{ SDL_SetWindowMinimumSize(self->handle, w, h); }
void shido_Window_setMaximumSize(shido_Window *self, int w, int h)
{ SDL_SetWindowMaximumSize(self->handle, w, h); }
void shido_Window_setSize(shido_Window *self, int w, int h)
{ SDL_SetWindowSize(self->handle, w, h); }
void shido_Window_setPosition(shido_Window *self, int x, int y)
{ SDL_SetWindowPosition(self->handle, x, y); }
void shido_Window_setTitle(shido_Window *self, const char *title)
{ SDL_SetWindowTitle(self->handle, title); }

void shido_Window_getFullscreen(shido_Window *self, bool out[2])
{
  Uint32 flags = SDL_GetWindowFlags(self->handle);
  out[0] = (flags & SDL_WINDOW_FULLSCREEN) || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP);
  out[1] = flags & SDL_WINDOW_FULLSCREEN_DESKTOP;
}
bool shido_Window_isVisible(shido_Window *self)
{ return SDL_GetWindowFlags(self->handle) & SDL_WINDOW_SHOWN; }
bool shido_Window_isResizable(shido_Window *self)
{ return SDL_GetWindowFlags(self->handle) & SDL_WINDOW_RESIZABLE; }
bool shido_Window_isBordered(shido_Window *self)
{ return !(SDL_GetWindowFlags(self->handle) & SDL_WINDOW_BORDERLESS); }
bool shido_Window_isMaximized(shido_Window *self)
{ return SDL_GetWindowFlags(self->handle) & SDL_WINDOW_MAXIMIZED; }
bool shido_Window_isMinimized(shido_Window *self)
{ return SDL_GetWindowFlags(self->handle) & SDL_WINDOW_MINIMIZED; }
bool shido_Window_hasFocus(shido_Window *self)
{ return SDL_GetWindowFlags(self->handle) & SDL_WINDOW_INPUT_FOCUS; }
bool shido_Window_hasMouseFocus(shido_Window *self)
{ return SDL_GetWindowFlags(self->handle) & SDL_WINDOW_MOUSE_FOCUS; }

// SwapChain

shido_SwapChain::~shido_SwapChain()
{
  shido::Graphics::get().engine->destroy(handle);
}

shido_SwapChainRef* shido_SwapChain_new(shido_WindowRef *window)
{
  // get native window handle
  /// info
  void *whandle = nullptr;
  SDL_SysWMinfo winfo;
  SDL_VERSION(&winfo.version);
  if(!SDL_GetWindowWMInfo(window->ref->handle, &winfo)){
    shido::error(std::string("SDL: ")+SDL_GetError());
    return nullptr;
  }
  /// handle
  switch(winfo.subsystem){
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    case SDL_SYSWM_WINDOWS: whandle = (void*)winfo.info.win.window; break;
#endif
#ifdef SDL_VIDEO_DRIVER_X11
    case SDL_SYSWM_X11: whandle = (void*)winfo.info.x11.window; break;
#endif
    default: break;
  }
  if(!whandle){
    shido::error("Native window handle not supported.");
    return nullptr;
  }
  shido::Graphics &graphics = shido::Graphics::get();
  filament::SwapChain *handle = graphics.engine->createSwapChain(whandle);
  if(!handle){
    shido::error("Filament SwapChain creation failed.");
    return nullptr;
  }
  return new shido_SwapChainRef{std::make_shared<shido_SwapChain>(window, handle)};
}
