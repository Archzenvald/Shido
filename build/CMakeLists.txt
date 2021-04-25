# Shido and C++ dependencies must be compiled with the Filament settings.

cmake_minimum_required(VERSION 3.10)
project(shido)

# options
option(FILAMENT_BUILD "Filament's debug/release build path." "filament/release")

# dirs
set(LIB_DIRS
  ${FILAMENT_BUILD}/lib
)
set(INC_DIRS
  ${FILAMENT_BUILD}/include
)
link_directories(${LIB_DIRS})
include_directories(${INC_DIRS})

# sources
set(SRCS
  main.cpp
)

# libs
set(LIBS
  SDL2
  pthread
  dl
)
set(FI_LIBS
  filament
  backend
  ibl
  geometry
  vkshaders
  bluegl
  bluevk
  filabridge
  filaflat
  utils
  smol-v
)
foreach(LIB ${FI_LIBS})
  add_library(${LIB} STATIC IMPORTED)
  set_target_properties(${LIB} PROPERTIES IMPORTED_LOCATION ${FILAMENT_BUILD}/lib/lib${LIB}.a)
endforeach()

# build
add_executable(run main.cpp)
target_link_libraries(run ${LIBS} ${FI_LIBS})
