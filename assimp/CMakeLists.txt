cmake_minimum_required(VERSION 3.13...3.16)
include(CMakePrintHelpers)
include(FetchContent)

project(assimp_example VERSION 1.0 LANGUAGES C)

# required for GLU includes
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Use DownloadProject: https://github.com/Crascit/DownloadProject
# cmake's ExternalProject < 3.8.0 has bugs when using URL download,
# so don't attempt caching if using an older version
# if (CMAKE_VERSION VERSION_LESS 3.8)
#     set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
# else()
#     set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
# endif()

# Add our project-specific Modules directory to the cmake module search path
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# include(DownloadProject)
# download_project(PROJ     assimp
#                  URL      https://github.com/assimp/assimp/archive/v4.1.0.tar.gz
#                  URL_HASH SHA1=ce3589f9455c743e993fd802bdaaed72838cd3f4
#                  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
# )
# FetchContent_Declare(
#   assimp
#   URL      https://github.com/assimp/assimp/archive/v4.1.0.tar.gz
#   URL_HASH SHA1=ce3589f9455c743e993fd802bdaaed72838cd3f4
# )

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG        v5.0.1
)

# if(${CMAKE_VERSION} VERSION_LESS 3.14)
#   macro(FetchContent_MakeAvailable NAME)
#     FetchContent_GetProperties(${NAME})
#     if(NOT ${NAME}_POPULATED)
#       FetchContent_Populate(${NAME})
#       add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
#     endif()
#   endmacro()
# endif()

# FetchContent_MakeAvailable(assimp)
FetchContent_GetProperties(assimp)
string(TOLOWER "assimp" lcName)
if(NOT ${lcName}_POPULATED)
  FetchContent_Populate(assimp)

# When including the library, no need for external tools
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)

# When including the library, no need for tests
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)

# This importer uses raw malloc()/free() calls, 
set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "" FORCE)

# Force Assimp to build its internal copy of zlib
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

  add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR})
endif()

# add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})


add_executable(assimp_simpleogl
  src/Sample_SimpleOpenGL.c
)

target_include_directories(assimp_simpleogl
  PUBLIC
  # Theoretically cmake should automatically pick up this directory, but it's easier to explicitly list it here.
  # "${assimp_SOURCE_DIR}/include"
  # ${assimp_INCLUDE_DIR}
  # Assimp builds a custom config.h as part of its build, so also include the binary directory
  # "${assimp_BINARY_DIR}/include"
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  )

target_link_libraries(assimp_simpleogl
  OpenGL::GL
  # OpenGL::OpenGL
  # ${GLUT_LIBRARIES}
  GLU
  glut
  assimp
)
cmake_print_properties(
    TARGETS assimp_simpleogl
    PROPERTIES LINK_LIBRARIES INCLUDE_DIRECTORIES
)

# ./assimp_simpleogl assimp-src/test/models-nonbsd/X/dwarf.x
