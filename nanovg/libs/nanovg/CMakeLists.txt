message(STATUS "processing nanovg")

include_directories(src)
add_library(nanovg
  src/nanovg.c
)
