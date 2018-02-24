# Open Asset Import Library(assimp)
[Assimp](http://assimp.org/) is a portable library to import 3D model formats in a uniform manner. It is an example of a well-meaning complicated import: the project maintains their own CMake system, but it is not usually installed directly to a packaging system.

Since the library is special-purpose enough to assume it will not be present, we use the excellent [DownloadProject](https://github.com/Crascit/DownloadProject) CMake module to acquire the source at build-time, then incorporate it into our CMake build using `add_subdirectory()`

## Requirements:
### Linux:
  - freeglut3-dev
  - libxmu-dev

## Known bugs
On OSX, if minizip is already installed on the system, linking to minizip during build finish may fail. 
This is due to assimp using outdated pkg-config macros from OGRE, which will automatically pick up the wrong link directory due to a [pkg-config quirk in CMake](https://cmake.org/Bug/view.php?id=15804)

## Project Layout

```
assimp
|-- CMakeLists.txt
|-- README.md
|-- cmake
|   `-- Modules
|       |-- DownloadProject.CMakeLists.cmake.in
|       `-- DownloadProject.cmake
`-- src
    `-- Sample_SimpleOpenGL.c
```

## CMakeLists walkthrough
### CMakeLists.txt

Declare our minimum CMake. DownloadProject is advanced enough that CMake 3.0 should be required.
```
cmake_minimum_required(VERSION 3.0)
```
Declare our project. This should always be the first statement outside of `cmake_minimum_required`, as most variables will not exist until this call.
```
project(assimp_example)
```

We require OpenGL and GLUT, so issue `find_package` calls to pick them up.
```
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
```

Before we load the DownloadProject module, we need to check CMake version: CMake < 3.8.0 has bugs in ExternalProject when using URL download, so don't attempt caching if using an older version
```
if (CMAKE_VERSION VERSION_LESS 3.8)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()
```

Add our project-specific Modules directory to the cmake module search path
```
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
```

Finally, include the DownloadProject module and set our assimp download location.
```
include(DownloadProject)
download_project(PROJ     assimp
                 URL      https://github.com/assimp/assimp/archive/v4.1.0.tar.gz
                 URL_HASH SHA1=ce3589f9455c743e993fd802bdaaed72838cd3f4
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
```

Assimp provides a CMake system, so we can set variables prior to `add_subdirectory`.

Notably: we do not require the extra tools or tests, so we can disable them. The Q3BSP importer has raw malloc()/free() calls, so we prefer not to build that importer. Finally, we restrict assimp to using its embedded copy of zlib to avoid library linkage issues.

Note that we use `CACHE BOOL "" FORCE` in our `set` commands. This is to get around a quirk of using assimp in a subdirectory provided by DownloadProject: normally we could simply `set` these and they would be picked up. But we need to force these in the top-level cache to ensure the separate download/src projects pick them up. This is a rare usage of using the Cache directly, and it is not encouraged for regular use.
```
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
```

Since assimp will be placed as two separate projects, we need to add both subdirectories(in particular, build-specific config headers will only be generated in ONE of them)
```
add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
```

Include our directories. Theoretically CMake should automatically pick up the Assimp directory, but it's easier to explicitly list it here to avoid autodetection issues.
```
include_directories(include
  "${assimp_SOURCE_DIR}/include"
  "${assimp_BINARY_DIR}/include"
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  )
```

Add our executable target.
```
add_executable(assimp_simpleogl
  src/Sample_SimpleOpenGL.c
)
```

Link our libraries. We have a `assimp` library variable at this point thanks to the `add_subdirectory` calls.
```
target_link_libraries(assimp_simpleogl
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
  assimp
)
```

## Use
Let's make our build dir and run CMake. Note that as part of this, the Assimp source file will be downloaded BEFORE we issue a `make` call.
```
$ mkdir build
$ cd build
$ cmake ..
```
Make our project:
```
$ make
```
Then we can run our executable, using a sample file from the distribution.
```
$ ./assimp_simpleogl assimp-src/test/models-nonbsd/X/dwarf.x
```
