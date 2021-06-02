// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef HPP_SHIDO_VIEW
#define HPP_SHIDO_VIEW

#include "View.h"

#include "../API.hpp"
#include "../graphics.hpp"
#include <filament/View.h>

SHIDO_HANDLE_HPP(View)

struct shido_View{
  filament::View *handle;
  shido_View(filament::View *_handle): handle(_handle){}
  ~shido_View();
};

#endif
