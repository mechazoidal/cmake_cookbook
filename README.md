# CMake Cookbook
This is a collection of subprojects showing various advanced facets of [CMake](https://cmake.org). It started out as a personal tool-evaluation repository for graphic and networking libraries, and shows some of the ways I use CMake.

The "source" files being compiled in these examples are taken directly from the project being shown. Only CMake is on display here.

If you've never used CMake before, please see [A Brief Beginner's Guide to CMake](https://github.com/pyk/cmake-tutorial), which served as inspiration for releasing this repository.

## Use
Each project has a README detailing sub-requirements, showing the project layout, and walking through the CMakeLists.txt files. 

Generally to build each, the following usage is encouraged:
```
$ mkdir build
$ cd build
$ cmake ..
$ <build system invocation, usually 'make'>
```

This is what's known as an "out-of-source" build, and it is strongly encouraged with CMake. There are a few major advantages in CMake:
  - There will be a LOT of files generated, and it's easier to have a `build/*` directive in your SCM ignore file, versus manually cleaning out after a build.
  - when creating/debugging a CMakeLists.txt file, it's easy to remove the directory and not have to worry about any lingering CMake variables hiding in CMakeCache.txt or other locations. Subsequent `cmake`/`make` calls will NOT remove variables you might have set in previous versions of your CMakeLists.txt!
  - it's easy to search through the directory to find out what a 3rd-party library is trying to do while debugging a CMakeLists.txt file

Don't forget there are many ways of running CMake beyond the standard CLI invocation! See the official [Running CMake](https://cmake.org/runningcmake/) page for more.

## Tested Platforms
  - OpenBSD 6.2
  - OSX 10.11 w/ Macports 2.4.2
  - Debian stretch

There should be no issues with running these examples on Windows, but no testing has been performed due to lack of access to a Windows system.

## Requirements:
### Linux:
  - build-essential
  - git
  - cmake
  - pkg-config

### OSX/BSD:
  - git
  - cmake
  - pkg-config

## Licensing
The base CMakeLists.txt and README.md files in each directory were created for the cmake_cookbook project, and are covered under the terms of the MIT License detailed in the LICENSE file. 

The CMakeLists.txt files in nanovg/libs/nanovg/ and imgui/libs/imgui were also created for the cmake_cookbook, and are also covered under the MIT License.

Code samples in the src/ directories are taken from the projects being shown and should be considered to be under the license for that specific project.

In the interest of having a working example for nanovg, the nanovg/media directory contains a copy of the "NotoSansUI-Regular.ttf" file from [Google's Noto fonts collection](https://www.google.com/get/noto/) , licensed under SIL OFL 1.1.

