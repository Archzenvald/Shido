// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_VIEW
#define H_SHIDO_VIEW

#ifdef __cplusplus
extern "C"{
#endif

#include "../API.h"

SHIDO_HANDLE_H(View)

// Create view.
// return new reference or NULL on failure (error)
SHIDO_API shido_ViewRef* shido_View_new();

#ifdef __cplusplus
}
#endif

#endif
