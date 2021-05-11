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

-- C API
local ffi = require("ffi")
ffi.cdef[[
const char* shido_core_getWorkingDirectory();
const char* shido_core_getExecutableDirectory();
bool shido_core_init();
void shido_core_quit();
void shido_core_sleep(double time);
]]
local L = ffi.load("shido")
-- init module
shido = {} -- shido first init
local core = {}
shido.core = core

function core.getWorkingDirectory()
  return ffi.string(L.shido_core_getWorkingDirectory())
end
function core.getExecutableDirectory()
  return ffi.string(L.shido_core_getExecutableDirectory())
end
function core.init() return L.shido_core_init() end
function core.quit() L.shido_core_quit() end
function core.sleep(time) L.shido_core_sleep(time) end

return core
