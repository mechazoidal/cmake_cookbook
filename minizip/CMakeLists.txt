cmake_minimum_required(VERSION 3.1)
project(test_minizip)

find_package(zlib)
find_package(PkgConfig)
pkg_check_modules(UNZIP minizip)

include_directories(include
  ${UNZIP_INCLUDEDIR}
)

find_library(minizip_LIBRARY minizip)

add_executable(minizip
  src/minizip.c
)

add_executable(miniunzip
  src/miniunzip.c
)

target_link_libraries(minizip
  ${ZLIB_LIBRARIES}
  ${minizip_LIBRARY}
)

target_link_libraries(miniunzip
  ${ZLIB_LIBRARIES}
  ${minizip_LIBRARY}
)
