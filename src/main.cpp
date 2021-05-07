#include <iostream>
#include <shido/core.h>

int main(int argc, char **argv)
{
  std::cout << shido_core_getWorkingDirectory() << std::endl;
  std::cout << shido_core_getExecutableDirectory() << std::endl;
  return 0;
}
