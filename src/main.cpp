#include <iostream>
#include <shido/core.h>
#include <luajit-2.0/lua.hpp>

// adapted error handling snippets from LuaJIT/luajit.c

static int traceback(lua_State *L)
{
  if (!lua_isstring(L, 1)) { /* Non-string error object? Try metamethod. */
    if (lua_isnoneornil(L, 1) ||
        !luaL_callmeta(L, 1, "__tostring") ||
        !lua_isstring(L, -1))
      return 1;  /* Return non-string error object. */
    lua_remove(L, 1);  /* Replace object by result of __tostring metamethod. */
  }
  luaL_traceback(L, L, lua_tostring(L, 1), 1);
  return 1;
}

static int report(lua_State *L, int status)
{
  if(status && !lua_isnil(L, -1)){
    const char *msg = lua_tostring(L, -1);
    if(msg == NULL) msg = "(error object is not a string)";
    std::cerr << msg << std::endl;
    lua_pop(L, 1);
  }
  return status;
}

// boot code
static const char *lua_boot =
  "local exec_path = ...\n"
  "package.path = package.path..\";\"..exec_path..\"?.lua\"\n"
  "require(\"shido.boot\")(select(2, ...))\n";

int main(int argc, char **argv)
{
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  int status = luaL_loadstring(L, lua_boot);
  if(status == 0){
    if(lua_checkstack(L, argc+1) != 0){
      // push exec path
      lua_pushstring(L, shido_core_getExecutableDirectory());
      // push arguments
      for(int i = 1; i < argc; i++)
        lua_pushstring(L, argv[i]);
      // error handling
      int base = lua_gettop(L)-argc;
      lua_pushcfunction(L, traceback);
      lua_insert(L, base);
      // call
      report(L, lua_pcall(L, argc, 0, base));
    }
    else
      std::cerr << "Lua stack exceeded by command-line arguments." << std::endl;
  }
  else
    report(L, status);
  lua_close(L);
  return 0;
}
