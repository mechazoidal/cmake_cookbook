# ImGui
[ImGui](https://github.com/ocornut/imgui) is a slim GUI library for C++. It is framework-agnostic, merely outputting a list of draw commands. This project shows the use of OpenGL, with window support from both GLFW and SDL2.

Since ImGui does not enforce any project layout, its files have been reorganized into a separate library directory. No changes have been made, and this should not be considered gospel: it's just one of many ways a developer could include them.

## Requirements

Linux:
  - libsdl2-dev

BSD:
  - sdl2

OSX:
  - LibSDL2

## Project Layout

```
imgui
|-- CMakeLists.txt
|-- README.md
|-- include
|   |-- imgui_impl_glfw.h
|   `-- imgui_impl_sdl.h
|-- libs
|   `-- imgui
|       |-- CMakeLists.txt
|       |-- LICENSE.txt
|       |-- imgui.cpp
|       |-- imgui_demo.cpp
|       |-- imgui_draw.cpp
|       `-- include
|           |-- imconfig.h
|           |-- imgui.h
|           |-- imgui_internal.h
|           |-- stb_rect_pack.h
|           |-- stb_textedit.h
|           `-- stb_truetype.h
`-- src
    |-- imgui_impl_glfw.cpp
    |-- imgui_impl_sdl.cpp
    |-- main.cpp
    `-- main_sdl.cpp
```

## CMakeLists walkthrough
### CMakeLists.txt
Declare our minimum cmake. There are no real advanced features used, so I usually use 2.8 as an absolute minimum. In 2018+ it's probably safe to use at least 3.0.
```
cmake_minimum_required(VERSION 2.8)
```
Declare our project. This should always be the first statement outside of `cmake_minimum_required`, as most variables will not exist until this call.
```
project(imgui_example)
```

glfw is usually shipped as 'glfw3', so take that into account. Note the use of `CONFIG` in the `find_package` call: this is because CMake ships a `glfw3Config.cmake` file OUTSIDE of our project.
This [StackOverflow answer](https://stackoverflow.com/questions/20746936/cmake-of-what-use-is-find-package-if-you-need-to-specify-cmake-module-path-an) is a good in-depth look at the difference between Module and Config modes in `find_package`
```
find_package(glfw3 CONFIG REQUIRED)
```
OpenGL(specifically GLU) is required, so request it here
```
find_package(OpenGL)
```

CMake has shipped a FindSDL2.cmake module for quite awhile, so a simple `find_package` is all that's required.
```
find_package(SDL2)
```

We have imported all of the packages we need, so it is safe to include the ImGui subdirectory in `libs`.
One of the easily-overlooked quirks of CMake is that every CMakeLists.txt file creates its own variable space. Much like `fork()` in Unix, the child CMakeLists.txt file will INHERIT variables from the parent, but after that is expected to keep its own. If you expect to use libraries or variables in subdirectories, they must be set BEFORE the `add_subdirectory` call.
(There are ways around this as demonstrated in the _assimp_ project, but they are not meant to be used on a regular basis)
```
add_subdirectory(libs/imgui)
```

Depending on how SDL2 is installed, it may require X11 libraries. Most systems will handle this OK, but OSX has dropped X11 out of its main developer trees. Most OSX packaging systems will then include it, but this isn't detected-by-default with CMake.

We use a simple conditional to check for an OSX system, then add the extra `find_package` and `include_directories` list. 
```
if(APPLE)
  find_package(X11)
  include_directories(include
    libs/imgui/include
    ${OPENGL_INCLUDE_DIR}
    ${glfw3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${X11_INCLUDE_DIR}
  )
```
If we are not in OSX, there's nothing to do.
```
else()
  include_directories(include
    libs/imgui/include
    ${OPENGL_INCLUDE_DIR}
    ${glfw3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
  )
```
Explicitly close our `if` tree. The `if` command is one of the oldest in CMake, so it still retains a few quirks. Happily, the `APPLE` flag is internal to CMake, so there is no string-escaping required.
```
endif(APPLE)
```

Declare our OpenGL2 example using GLFW
```
add_executable(opengl2_example
  src/main.cpp
  src/imgui_impl_glfw.cpp
)
```

Link the ImGui, opengl, and glfw libraries. We have a `imgui` library variable at this point thanks to the `add_subdirectory` call earlier.
```
target_link_libraries(opengl2_example
  imgui
  ${OPENGL_LIBRARIES}
  glfw
)
```

Declare our OpenGL2 example using SDL2
```
add_executable(sdl_opengl2_example
  src/main_sdl.cpp
  src/imgui_impl_sdl.cpp
)
```

Link against our requested libraries.
```
target_link_libraries(sdl_opengl2_example
  imgui
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)
```
### libs/imgui/CMakeLists.txt
Since we are in a subdirectory, we already have a cmake version requirement and a project declared. All that's left is to just declare the library that ImGui builds.

I like to put `STATUS` messages in subdirectory files, if only because it can help debugging later. There is no requirement to do so.
```
message(STATUS "processing imgui")
```

ImGui provides a separate include directory.
```
include_directories(include)
```
ImGui is a few source files. By default `add_library` will build a static library, which is fine for a single executable.
```
add_library(imgui
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
)
```
## Use
Let's make our build dir and run cmake:
```
$ mkdir build
$ cd build
$ cmake ..
```

Then we can make our project. Note that ImGui will be built as a static library before our executable:
```
$ make
Scanning dependencies of target imgui
[ 10%] Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui.cpp.o
[ 20%] Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui_demo.cpp.o
[ 30%] Building CXX object libs/imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o
[ 40%] Linking CXX static library libimgui.a
[ 40%] Built target imgui
Scanning dependencies of target sdl_opengl2_example
[ 50%] Building CXX object CMakeFiles/sdl_opengl2_example.dir/src/main_sdl.cpp.o
[ 60%] Building CXX object CMakeFiles/sdl_opengl2_example.dir/src/imgui_impl_sdl.cpp.o
[ 70%] Linking CXX executable sdl_opengl2_example
[ 70%] Built target sdl_opengl2_example
Scanning dependencies of target opengl2_example
[ 80%] Building CXX object CMakeFiles/opengl2_example.dir/src/main.cpp.o
[ 90%] Building CXX object CMakeFiles/opengl2_example.dir/src/imgui_impl_glfw.cpp.o
[100%] Linking CXX executable opengl2_example
[100%] Built target opengl2_example
```
And then we can run our executables:
```
$ ./opengl2_example
$ ./sdl_opengl2_example
```
