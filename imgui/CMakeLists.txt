cmake_minimum_required(VERSION 2.8)
project(imgui_example)

# For the straight OpenGL2 example
find_package(glfw3 CONFIG REQUIRED)
# required for GLU includes
find_package(OpenGL)

# No need for a specialised FindSDL2.cmake module, as of 3.9.3+(?)
find_package(SDL2)

add_subdirectory(libs/imgui)

if(APPLE)
  # OSX does not include X11 by default and some SDL2 installations require it, so add it here.
  find_package(X11)
  include_directories(include
    libs/imgui/include
    ${OPENGL_INCLUDE_DIR}
    ${glfw3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
  )
else()
  include_directories(include
    libs/imgui/include
    ${OPENGL_INCLUDE_DIR}
    ${glfw3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
  )
endif(APPLE)
# The sample using OpenGL2 and GLFW window
add_executable(opengl2_example
  src/main.cpp
  src/imgui_impl_glfw.cpp
)

target_link_libraries(opengl2_example
  imgui
  ${OPENGL_LIBRARIES}
  glfw
)

# The sample using OpenGL2 and SDL window
add_executable(sdl_opengl2_example
  src/main_sdl.cpp
  src/imgui_impl_sdl.cpp
)

target_link_libraries(sdl_opengl2_example
  imgui
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)
