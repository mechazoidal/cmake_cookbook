cmake_minimum_required(VERSION 3.13...3.16)
include(CMakePrintHelpers)

project(nanovg_torus VERSION 1.0 LANGUAGES C CXX)

# This will pull in the OpenGL::GL and OpenGL::GLU link targets
find_package(OpenGL REQUIRED)

# glew's library is CAPITALIZED..
find_package(GLEW REQUIRED)

# glfw3's is NOT
find_package(glfw3 3.2 REQUIRED)

add_library(nanovg "")
add_subdirectory(libs/nanovg)


add_executable(nanovg_torus
  src/torus.cpp
)

target_link_libraries(nanovg_torus
  PRIVATE
  nanovg
  GLEW::GLEW
  OpenGL::GLU
  glfw
  OpenGL::GL
)
