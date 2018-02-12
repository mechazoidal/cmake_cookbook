message(STATUS "processing imgui")

include_directories(include)
add_library(imgui
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
)
