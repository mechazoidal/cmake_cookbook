cmake_minimum_required(VERSION 3.13...3.16)
include(CMakePrintHelpers)

project(imgui_example VERSION 1.1 LANGUAGES C CXX)

# For the straight OpenGL2 example
find_package(glfw3 3.3 REQUIRED)
# required for GLU includes and linking
find_package(OpenGL REQUIRED)

# For using OpenGL2 with SDL window
find_package(SDL2 REQUIRED)

add_library(imgui "")
add_subdirectory(libs/imgui)

# The sample using OpenGL2 and GLFW window
add_executable(opengl2_example
  src/main.cpp
  src/imgui_impl_glfw.cpp
  src/imgui_impl_opengl2.cpp
)

target_link_libraries(opengl2_example
  PRIVATE
  imgui
  OpenGL::GL
  glfw
)

# The sample using OpenGL2 and SDL window
add_executable(sdl_opengl2_example
  src/main_sdl.cpp
  src/imgui_impl_sdl.cpp
  src/imgui_impl_opengl2.cpp
)

target_link_libraries(sdl_opengl2_example
  PRIVATE
  imgui
  SDL2
  OpenGL::GL
)

# if(APPLE)
#   # OSX does not include X11 by default and some SDL2 installations require it, so add it here.
#   find_package(X11)
#   include_directories(include
#     ${OPENGL_INCLUDE_DIR}
#     ${glfw3_INCLUDE_DIRS}
#     ${SDL2_INCLUDE_DIRS}
#     ${X11_INCLUDE_DIR}
#   )
# else()
  target_include_directories(opengl2_example
    PUBLIC
    include
    ${OPENGL_INCLUDE_DIR}
    ${glfw3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
  )
  target_include_directories(sdl_opengl2_example
    PUBLIC
    include
    ${OPENGL_INCLUDE_DIR}
    ${glfw3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
  )
# endif(APPLE)
cmake_print_properties(
    TARGETS opengl2_example sdl_opengl2_example
    PROPERTIES LINK_LIBRARIES INCLUDE_DIRECTORIES
)
