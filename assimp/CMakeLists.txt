cmake_minimum_required(VERSION 2.8)
project(assimp_example)

# required for GLU includes
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Use DownloadProject: https://github.com/Crascit/DownloadProject
# DownloadProject uses variables specific to 3.2+ : prevent errors on older versions
if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

# Add our project-specific Modules directory to the cmake module search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include(DownloadProject)
download_project(PROJ     assimp
                 URL      https://github.com/assimp/assimp/archive/v4.1.0.tar.gz
                 URL_HASH SHA1=ce3589f9455c743e993fd802bdaaed72838cd3f4
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# When including the library, no need for external tools
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)

# When including the library, no need for tests
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)

# This importer uses raw malloc()/free() calls, 
set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "" FORCE)

# Force Assimp to build its internal copy of zlib
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})

include_directories(include
  # Theoretically cmake should automatically pick up this directory, but it's easier to explicitly list it here.
  "${assimp_SOURCE_DIR}/include"
  # Assimp builds a custom config.h as part of its build, so also include the binary directory
  "${assimp_BINARY_DIR}/include"
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  )

add_executable(assimp_simpleogl
  src/Sample_SimpleOpenGL.c
)

target_link_libraries(assimp_simpleogl
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
  assimp
)

# ./assimp_simpleogl assimp-src/test/models-nonbsd/X/dwarf.x
