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
set(H_SRCS
  ../src/c/core.h
)
set(I_SRCS
  ../src/c/core.cpp
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
target_link_libraries(shido-run shido)
