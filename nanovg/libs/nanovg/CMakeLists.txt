target_include_directories(nanovg
  PUBLIC
  src
)

target_sources(nanovg
  PRIVATE
  src/stb_truetype.h
  src/nanovg_gl.h
  src/fontstash.h
  src/nanovg_gl_utils.h
  src/stb_image.h
  src/nanovg.h
  src/nanovg.c
)
