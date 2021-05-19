// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)
/*
MIT License

Copyright (c) 2021 Archzenvald

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 * The shido API is made of modules and handles. Each exposed type or function
 * is prefixed by "shido_". A function/method can also be prefixed by a
 * namespace as "shido_<namespace>_" where namespace may be a module name or handle
 * type.
 *
 * An handle is made up of an object type and a reference type , e.g.
 * "shido_Window" and "shido_WindowRef". The first is used to manipulate the
 * object while the second manages its lifespan/validity.  To use an handle, a
 * reference must first be acquired; then the object handle can be used as long
 * as the reference is valid.
 *
 * Sometimes, parts of the API may depend on third-party library definitions to
 * prevent redundancy (e.g. SDL types/enums), but the API wraps all the calls
 * to that library.
 */

#ifndef H_SHIDO_CORE
#define H_SHIDO_CORE

#ifdef __cplusplus
extern "C"{
#endif

#include "API.h"

// Error handling.
// Set C API error.
SHIDO_API void shido_core_error(const char* err);
// Get last C API error.
SHIDO_API const char* shido_core_getError();

SHIDO_API const char* shido_core_getWorkingDirectory();
SHIDO_API const char* shido_core_getExecutableDirectory();
// Init.
// return false on failure (error)
SHIDO_API bool shido_core_init();
SHIDO_API void shido_core_sleep(double time);
SHIDO_API double shido_core_getTime();

#ifdef __cplusplus
}
#endif

#endif
