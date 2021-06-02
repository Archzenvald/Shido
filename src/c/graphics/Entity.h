// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#ifndef H_SHIDO_ENTITY
#define H_SHIDO_ENTITY

#ifdef __cplusplus
extern "C"{
#endif

#include "../API.h"

SHIDO_HANDLE_H(Entity)

// Create entity.
// return new reference or NULL on failure (error)
SHIDO_API shido_EntityRef* shido_Entity_new();

#ifdef __cplusplus
}
#endif

#endif
