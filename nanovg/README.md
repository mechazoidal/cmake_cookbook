# NanoVG
[NanoVG](https://github.com/memononen/nanovg) is a small UI library for OpenGL, with an API modeled after the HTML5 Canvas API. Like [stb](https://github.com/nothings/stb), it's easy to include inside your project instead of importing a package from a repository. 

This source sample is from a [gist](https://gist.github.com/piaoger/66de3489d771c2ec57c7) showing how to render a simple torus and string using NanoVG. A CMakeLists.txt file was added to the nanovg directory to show usage of a user-defined pair of `add_library`/`add_subdirectory`.

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
Declare our minimum cmake version range. 3.13 should be considered a "minimum" in 2020 and most systems at the time of this writing usually have 3.16
```
cmake_minimum_required(VERSION 3.13...3.16)
```

Declare our project. This should always be the first statement outside of `cmake_minimum_required`, as most variables will not exist until this call.
Our sample source file is a C++ file and nanovg is a C library, so we hint to cmake that both languages will be used.
```
project(nanovg_torus VERSION 1.0 LANGUAGES C CXX)
```
OpenGL(specifically GLU) is required, so request it here. We can't continue without it, so it is marked as required.
```
find_package(OpenGL REQUIRED)
```

CMake's case-sensitivity for packages depends on the host OS's filesystem. GLEW is usually provided in ALL-CAPS, so request it here.
```
find_package(GLEW REQUIRED)
```

glfw is usually shipped as 'glfw3', so take that into account. We also request version 3.2 or higher of the package.
The previous version of this `find_package` example used Config mode but Kitware now recommends using [basic signatures](https://cmake.org/cmake/help/latest/command/find_package.html?highlight=find_package#basic-signature) unless you have a known reason.
```
find_package(glfw3 REQUIRED)
```

We have imported all of the packages we need, so now we need to create an internal project for nanovg. It is no longer considered best-practices to declare the library target in the subdirectory's CMakeLists.txt: remember that CMake variables exist only at the subdirectory level and are not exported back to the parent. Instead we declare an empty nanovg library target as a placeholder.

```
add_library(nanovg "")
add_subdirectory(libs/nanovg)
```

With all of our includes finished, declare our executable target. The sources consist only of `src/torus.cpp`
```
add_executable(nanovg_torus
  src/torus.cpp
)
```

Since the nanovg subdirectory already declares its own list of target include directories, and the torus example does not have any includes, we can procede straight to defining our target link libraries.

```
target_link_libraries(nanovg_torus
  PRIVATE
  nanovg
  GLEW::GLEW
  OpenGL::GLU
  glfw
  OpenGL::GL
)
```
### libs/nanovg/CMakeLists.txt
Since we are in a subdirectory, we already have a cmake version requirement, a project declared, and a `nanovg` library target to bind to. All that's left is to just declare the specifics of the nanovg library.
```

NanoVG mixes its includes and source, so set the `src/` directory for includes.
```
target_include_directories(nanovg
  PUBLIC
  src
)
```
NanoVG is a single source file.
```
target_sources(nanovg
  PRIVATE
  src/nanovg.c
)
```
## Use
Let's make our build dir and run cmake like usual:
```
$ mkdir build
$ cd build
$ cmake -S .. -B .
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
