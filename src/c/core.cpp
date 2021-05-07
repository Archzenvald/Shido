
#include "core.hpp"

const char* shido_core_getWorkingDirectory()
{
  const static utils::Path path = utils::Path::getCurrentDirectory();
  return path.c_str();
}

const char* shido_core_getExecutableDirectory()
{
  const static utils::Path path = utils::Path::getCurrentExecutable().getParent();
  return path.c_str();
}
