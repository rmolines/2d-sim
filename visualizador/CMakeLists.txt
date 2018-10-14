project(visualizador)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(PkgConfig REQUIRED)
# Find SDL2

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_gfx REQUIRED SDL2_gfx)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_gfx_INCLUDE_DIR})    

add_executable(visualizador main.cpp visualizador.cpp)
target_link_libraries(visualizador ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})

if("${STRATEGY} " STREQUAL "omp ")
    SET(CMAKE_CXX_FLAGS  " -fopenmp -O2 -Wall")
    message("OMP")
elseif("${STRATEGY} " STREQUAL "seq ")
    message("SEQ")
    SET(CMAKE_CXX_FLAGS  " -Wall -O2")
elseif("${STRATEGY} " STREQUAL "best ")
    message("BEST")
    SET(CMAKE_CXX_FLAGS  " -ffast-math -ftree-vectorize -mavx2 -O2 -fopenmp -Wall")
elseif("${STRATEGY} " STREQUAL "simd ")
    message("SIMD")
    SET(CMAKE_CXX_FLAGS  " -ffast-math -ftree-vectorize -mavx2 -O2 -Wall")
ENDIF()

