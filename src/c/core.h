#ifndef H_SHIDO_CORE
#define H_SHIDO_CORE

#ifdef __cplusplus
extern "C"{
#endif

#include "API.h"

API const char* shido_core_getWorkingDirectory();
API const char* shido_core_getExecutableDirectory();

#ifdef __cplusplus
}
#endif

#endif
