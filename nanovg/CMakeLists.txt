cmake_minimum_required(VERSION 2.8)
# use with piaoger/nanovg_torus.cpp , https://gist.github.com/piaoger/66de3489d771c2ec57c7
# Project structure:
# libs/nanovg/<src>
# also don't forget to change/add the font

project(nanovg_torus)

# required for GLU includes
find_package(OpenGL)

# glew's library is CAPITALIZED..
find_package(GLEW REQUIRED)

# glfw3's is NOT
find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(libs/nanovg)

include_directories(libs/nanovg/src
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  ${glfw3_INCLUDE_DIRS}
)

add_executable(nanovg_torus
  src/torus.cpp
)

target_link_libraries(nanovg_torus
  ${GLEW_LIBRARIES}
  nanovg
  glfw
  ${OPENGL_LIBRARIES}
)
