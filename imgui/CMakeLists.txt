cmake_minimum_required(VERSION 2.8)
project(imgui_example)

# required for GLU includes
find_package(OpenGL)

find_package(glfw3 CONFIG REQUIRED)
add_subdirectory(libs/imgui)

include_directories(include
  libs/imgui/include
  ${OPENGL_INCLUDE_DIR}
  ${glfw3_INCLUDE_DIRS}
)

# OpenBSD doesn't have OpenGL3 yet?
add_executable(opengl2_example
  src/main.cpp
  src/imgui_impl_glfw.cpp
)

target_link_libraries(opengl2_example
  imgui
  ${OPENGL_LIBRARIES}
  glfw
)
