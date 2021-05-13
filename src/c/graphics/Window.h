// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_WINDOW
#define H_SHIDO_WINDOW

#ifdef __cplusplus
extern "C"{
#endif

#include "../API.h"

SHIDO_HANDLE_H(Window)
SHIDO_API shido_WindowRef* shido_Window_new();

#ifdef __cplusplus
}
#endif

#endif
