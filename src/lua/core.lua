-- https://github.com/Archzenvald/Shido
-- MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)
--[[
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
]]

-- Framework's core module.

-- C API
local ffi = require("ffi")
ffi.cdef[[
const char* shido_core_getError();
void shido_core_warning(const char* warn);
const char* shido_core_getWorkingDirectory();
const char* shido_core_getExecutableDirectory();
bool shido_core_init();
void shido_core_sleep(double time);
double shido_core_getTime();
]]
local L = ffi.load("shido")
-- init module
shido = {} -- shido first init
local core = {}
shido.core = core

-- Error/warning handling.
--- Fatal error: the API cannot recover from the error, the user must handle it (throw).
--- Soft error: the error is non-fatal and signaled to the user (e.g. (ok, err) return values),  but can be ignored.
--- Warning: message not signaled through the API; printed to stderr.

-- Get last shido C API error.
function core.getError()
  return ffi.string(L.shido_core_getError())
end
-- Throw Lua error from the last shido C API error.
function core.error() error(core.getError()) end
function core.warning(warn) L.shido_core_warning(warn) end

function core.getWorkingDirectory()
  return ffi.string(L.shido_core_getWorkingDirectory())
end
function core.getExecutableDirectory()
  return ffi.string(L.shido_core_getExecutableDirectory())
end
function core.init()
  if not L.shido_core_init() then core.error() end
end
function core.sleep(time) L.shido_core_sleep(time) end
function core.getTime() return L.shido_core_getTime() end

return core
