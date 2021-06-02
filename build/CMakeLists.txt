# Shido and C++ dependencies must be compiled with the Filament settings.

cmake_minimum_required(VERSION 3.10)
project(shido)

# options
option(FILAMENT_BUILD "Filament's debug/release build path." "filament/release")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

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
set(H_SRCS
  ../src/c/API.h
  ../src/c/API.hpp
  ../src/c/core.h
  ../src/c/core.hpp
  ../src/c/graphics.h
  ../src/c/graphics.hpp
  ../src/c/graphics/Window.h
  ../src/c/graphics/Window.hpp
  ../src/c/graphics/Renderer.h
  ../src/c/graphics/Renderer.hpp
  ../src/c/graphics/View.h
  ../src/c/graphics/View.hpp
  ../src/c/graphics/Scene.h
  ../src/c/graphics/Scene.hpp
  ../src/c/graphics/Entity.h
  ../src/c/graphics/Entity.hpp
  ../src/c/event.h
  ../src/c/event.hpp
  ../src/c/input.h
  ../src/c/input.hpp
)
set(I_SRCS
  ../src/c/core.cpp
  ../src/c/graphics.cpp
  ../src/c/graphics/Window.cpp
  ../src/c/graphics/Renderer.cpp
  ../src/c/graphics/View.cpp
  ../src/c/graphics/Scene.cpp
  ../src/c/graphics/Entity.cpp
  ../src/c/event.cpp
  ../src/c/input.cpp
)

# libs
set(LIBS
  SDL2
  pthread
  dl
)
set(FILAMENT_LIBS
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
foreach(LIB ${FILAMENT_LIBS})
  add_library(${LIB} STATIC IMPORTED)
  set_target_properties(${LIB} PROPERTIES IMPORTED_LOCATION ${FILAMENT_BUILD}/lib/lib${LIB}.a)
endforeach()

# build shido lib
add_library(shido SHARED ${H_SRCS} ${I_SRCS})
target_link_libraries(shido ${LIBS} ${FILAMENT_LIBS})

# build C includes
## copy script
file(WRITE ${CMAKE_BINARY_DIR}/copy_includes.cmake
  "file(COPY ${CMAKE_SOURCE_DIR}/../src/c/ DESTINATION include/shido/ FILES_MATCHING PATTERN *.h)\n"
  )
add_custom_command(TARGET shido
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/copy_includes.cmake)

# build Lua API
add_custom_target(shido-lua ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ../src/lua/ shido)

# build shido executable
add_executable(shido-run ../src/main.cpp)
target_include_directories(shido-run PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(shido-run shido luajit-5.1)
