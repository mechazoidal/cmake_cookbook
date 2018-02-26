# NanoVG
[NanoVG](https://github.com/memononen/nanovg) is a small UI library for OpenGL, with an API modeled after the HTML5 Canvas API. Like [stb](https://github.com/nothings/stb), it's easy to include inside your project instead of importing a package from a repository. 

This source sample is from a [gist](https://gist.github.com/piaoger/66de3489d771c2ec57c7) showing how to render a simple torus and string using NanoVG. A CMakeLists.txt file was added to the nanovg directory to show usage of a `add_subdirectory`.

Note that NanoVG does not provide fonts directly, expecting the user to pass locations during compile-time. In the interest of having a working example(and not trying to guess font paths), the "NotoSansUI-Regular.ttf" file is included from [Google's Noto fonts collection](https://www.google.com/get/noto/) , licensed under SIL OFL 1.1

## Requirements

Linux:
  - libglew-dev
  - libglfw3-dev

OSX:
  - glfw

BSD:
  - glew
  - glfw

## Project Layout
```
nanovg
|-- CMakeLists.txt
|-- README.md
|-- include
|-- libs
|   `-- nanovg
|       |-- CMakeLists.txt
|       |-- LICENSE.txt
|       |-- README.md
|       |-- premake4.lua
|       `-- src
|           |-- fontstash.h
|           |-- nanovg.c
|           |-- nanovg.h
|           |-- nanovg_gl.h
|           |-- nanovg_gl_utils.h
|           |-- stb_image.h
|           `-- stb_truetype.h
|-- media
|   |-- LICENSE
|   `-- NotoSansUI-Regular.ttf
`-- src
    `-- torus.cpp
```

## CMakeLists walkthrough
### CMakeLists.txt
Declare our minimum cmake. There are no real advanced features used, so I usually use 2.8 as an absolute minimum. In 2018+ it's probably safe to use at least 3.0.
```
cmake_minimum_required(VERSION 2.8)
```

Declare our project. This should always be the first statement outside of `cmake_minimum_required`, as most variables will not exist until this call.
```
project(nanovg_torus)
```
OpenGL(specifically GLU) is required, so request it here
```
# required for GLU includes
find_package(OpenGL)
```

CMake's case-sensitivity for packages depends on the host OS's filesystem. GLEW is usually provided in ALL-CAPS, so request it here.
```
find_package(GLEW REQUIRED)
```

glfw is usually shipped as 'glfw3', so take that into account. Note the use of `CONFIG` in the `find_package` call: this is because CMake ships a `glfw3Config.cmake` file OUTSIDE of our project.
This [StackOverflow answer](https://stackoverflow.com/questions/20746936/cmake-of-what-use-is-find-package-if-you-need-to-specify-cmake-module-path-an) is a good in-depth look at the difference between Module and Config modes in `find_package`
```
find_package(glfw3 CONFIG REQUIRED)
```

We have imported all of the packages we need, so it is safe to include the NanoVG subdirectory in `libs`.
One of the easily-overlooked quirks of CMake is that every CMakeLists.txt file creates its own variable space. Much like `fork()` in Unix, the child CMakeLists.txt file will INHERIT variables from the parent, but after that is expected to keep its own. If you expect to use libraries or variables in subdirectories, they must be set BEFORE the `add_subdirectory` call.

(There are ways around this as demonstrated in the _assimp_ project, but they are not meant to be used on a regular basis)
```
add_subdirectory(libs/nanovg)
```

With all of our includes finished, include directories.
```
include_directories(libs/nanovg/src
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  ${glfw3_INCLUDE_DIRS}
)
```

Declare our executable, found in `src/torus.cpp`
```
add_executable(nanovg_torus
  src/torus.cpp
)
```

Link against our libraries. We have a `nanovg` library variable at this point thanks to the `add_subdirectory` call earlier.
```
target_link_libraries(nanovg_torus
  ${GLEW_LIBRARIES}
  nanovg
  glfw
  ${OPENGL_LIBRARIES}
)
```
### libs/nanovg/CMakeLists.txt
Since we are in a subdirectory, we already have a cmake version requirement and a project declared. All that's left is to just declare the library that nanovg builds.

I like to put `STATUS` messages in subdirectory files, if only because it can help debugging later. There is no requirement to do so.
```
message(STATUS "processing nanovg")
```

NanoVG mixes its includes and source, so set the `src/` directory for includes.
```
include_directories(src)
```
NanoVG is a single source file. By default `add_library` will build a static library, which is fine for a single executable.
```
add_library(nanovg
  src/nanovg.c
)
```
## Use
Let's make our build dir and run cmake like usual:
```
$ mkdir build
$ cd build
$ cmake ..
```

Then we can make our project. Note that nanovg will be built as a static library before our executable:
```
$ make
Scanning dependencies of target nanovg
[ 25%] Building C object libs/nanovg/CMakeFiles/nanovg.dir/src/nanovg.c.o
[ 50%] Linking C static library libnanovg.a
[ 50%] Built target nanovg
Scanning dependencies of target nanovg_torus
[ 75%] Building CXX object CMakeFiles/nanovg_torus.dir/src/torus.cpp.o
[100%] Linking CXX executable nanovg_torus
```

And then we can run our executable:
```
$ ./nanovg_torus
```
