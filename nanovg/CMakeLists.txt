cmake_minimum_required(VERSION 2.8)
# use with piaoger/nanovg_torus.cpp , https://gist.github.com/piaoger/66de3489d771c2ec57c7
# Project structure:
# libs/nanovg/include/ (includes only)
# libs/nanovg/libnanovg.a
# libs/glfw (full source)
# also don't forget to change/add the font

project(nanovg_torus)

# required for GLU includes
find_package(OpenGL)

# glew's library is CAPITALIZED..
find_package(GLEW REQUIRED)

# glfw3's is NOT
find_package(glfw3 CONFIG REQUIRED)
#find_package(glfw REQUIRED)

add_subdirectory(libs/nanovg)

#include_directories(${GLEW_INCLUDE_DIRS})

# It seems to be almost impossible to add GLFW from an external pkgconfig, or as a CMake ExternalProject
# So just include the source dir, and import it as a subdirectory(which will then fill out all the correct variables)
#set(GLFW_DIR ${CMAKE_SOURCE_DIR}/libs/glfw)
#add_subdirectory(${GLFW_DIR})
#include_directories(${GLFW_DIR}/include)

# Include the nanovg static library(build it yourself using premake, and drop it in)
# TODO can nanovg be added to macports ?
#add_library(libnanovg STATIC IMPORTED)
#set_property(TARGET libnanovg PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/nanovg/libnanovg.a)
#include_directories(libs/nanovg/include)

include_directories(libs/nanovg/src
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  #${glfw_INCLUDE_DIRS}
  ${glfw3_INCLUDE_DIRS}
  #${glu_INCLUDE_DIRS}
)

add_executable(nanovg_torus
  torus.cpp
)

target_link_libraries(nanovg_torus
  #${GLEW_LIBRARY}
  #${glfw3_LIBRARIES}
  ${GLEW_LIBRARIES}
  #${OPENGL_LIBRARY}
  #${glfw3_LIBRARY}
  #${glfw_LIBRARY}
  #glfw3
  #glu
  nanovg
  #${GLEW_LIBRARIES}
  #glew
  glfw
  #GLEW
  #glfw3
  #${GLFW_LIBRARIES}
)

# TODO insert font using:
# fc-list | grep Roboto-Regular | cut -d: -f1
