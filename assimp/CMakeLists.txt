cmake_minimum_required(VERSION 3.13...3.16)

include(CMakePrintHelpers)
include(FetchContent)

project(assimp_example VERSION 1.0 LANGUAGES C CXX)

# required for GLU includes
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG        v5.0.1
)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
  macro(FetchContent_MakeAvailable NAME)
    FetchContent_GetProperties(${NAME})
    if(NOT ${NAME}_POPULATED)
      FetchContent_Populate(${NAME})
      add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
    endif()
  endmacro()
endif()

# FetchContent_MakeAvailable(assimp) # can't use because we need to set vars
FetchContent_GetProperties(assimp)
string(TOLOWER "assimp" lcName)
if(NOT ${lcName}_POPULATED)
  FetchContent_Populate(assimp)

  # TODO
  cmake_policy(SET CMP0042 NEW)

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

add_executable(assimp_simpleogl
  src/Sample_SimpleOpenGL.c
)

target_include_directories(assimp_simpleogl
  PUBLIC
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  )

target_link_libraries(assimp_simpleogl
  OpenGL::GL
  OpenGL::GLU
  GLUT::GLUT
  assimp
)
cmake_print_properties(
    TARGETS assimp_simpleogl
    PROPERTIES LINK_LIBRARIES INCLUDE_DIRECTORIES
)

# ./assimp_simpleogl assimp-src/test/models-nonbsd/X/dwarf.x
