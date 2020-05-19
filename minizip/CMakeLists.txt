cmake_minimum_required(VERSION 3.13...3.16)
include(CMakePrintHelpers)
project(test_minizip VERSION 1.0 LANGUAGES C)

find_package(ZLIB REQUIRED)
find_package(PkgConfig)
pkg_check_modules(UNZIP minizip)

include_directories(include
  ${UNZIP_INCLUDEDIR}
)

# TODO document "Little libraries" https://cliutils.gitlab.io/modern-cmake/chapters/features/small.html
# find_library(ZLIB z)

find_library(minizip_LIBRARY minizip)

add_executable(minizip_e
  src/minizip.c
)

add_executable(miniunzip_e
  src/miniunzip.c
)

target_link_libraries(minizip_e
  PRIVATE
  z
  minizip
)

target_link_libraries(miniunzip_e
  PRIVATE
  z
  minizip
)
cmake_print_properties(
    TARGETS minizip_e
    PROPERTIES LINK_LIBRARIES INCLUDE_DIRECTORIES
)
