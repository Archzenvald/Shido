// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_SCENE
#define H_SHIDO_SCENE

#ifdef __cplusplus
extern "C"{
#endif

#include "../API.h"

SHIDO_HANDLE_H(Scene)

// Create scene.
// return new reference or NULL on failure (error)
SHIDO_API shido_SceneRef* shido_Scene_new();

#ifdef __cplusplus
}
#endif

#endif
