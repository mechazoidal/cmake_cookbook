# ZeroMQ
ZeroMQ(or ØMQ in UTF-8) is a high-performance async messaging library with an interface resembling Berkeley sockets. Though the core is in C++, the project leads prefer to keep the library interface in C and as simple as possible.

Up until version 4.2(per [this issue](https://github.com/zeromq/cppzmq/issues/127)), ZMQ did not ship a FindZeroMQ.cmake file. Since some packaging systems are still at 4.1, we include the official FindZeroMQ.cmake file, in cmake/Modules.


## Requirements:
### Linux:
  - libczmq-dev

### BSD:
  - zeromq

### OSX:
  - zmq

## Project Layout
```
zmq
|-- CMakeLists.txt
|-- README.md
|-- cmake
|   `-- Modules
|       |-- FindZeroMQ-LICENSE.txt
|       |-- FindZeroMQ.cmake
|       `-- README.txt
|-- include
|   |-- config.h
|   `-- zhelpers.h
`-- src
    |-- config.c
    |-- version.c
    |-- wuclient.c
    `-- wuserver.c
```

## CMakeLists walkthrough
### CMakeLists.txt
Declare our minimum cmake. There are no real advanced features used, so I usually use 2.8 as an absolute minimum. In 2018+ it's probably safe to use at least 3.0.
```
cmake_minimum_required(VERSION 2.8)
```

Declare our project. This should always be the first statement outside of `cmake_minimum_required`, as most variables will not exist until this call.
```
project(zmq_example)
```

Add our project-specific Modules directory to the cmake module search path
```
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
```

With our project module set, find the library in the system.
```
find_package(ZeroMQ)
```

An example of echoing a variable set by `find_package`: CMake will already echo the version it finds, but try moving this before the `find_package` call and see what is printed.
```
message(STATUS "ZeroMQ version: ${ZeroMQ_VERSION}")
```

`include_directories` applies to ALL following targets once set.
```
include_directories(include
  ${ZeroMQ_INCLUDE_DIR}
)
```

Declare our executable targets and their sources
```
add_executable(wuclient
  src/wuclient.c
)
add_executable(wuserver
  src/wuserver.c
)
add_executable(version
  src/version.c
)
```

Link our executables.
Note that libraries may be linked to a target immediately after declaring it
with `add_executable`, but I prefer to keep them in one section.
```
target_link_libraries(wuclient
  ${ZeroMQ_LIBRARIES}
)

target_link_libraries(wuserver
  ${ZeroMQ_LIBRARIES}
)

target_link_libraries(version
  ${ZeroMQ_LIBRARIES}
)
```

## Use
Let's make our build dir and run cmake like usual:
```
$ mkdir build
$ cd build
$ cmake ..
```

Then we can make our project.
```
$ make
Scanning dependencies of target version
[ 16%] Building C object CMakeFiles/version.dir/src/version.c.o
[ 33%] Linking C executable version
[ 33%] Built target version
Scanning dependencies of target wuserver
[ 50%] Building C object CMakeFiles/wuserver.dir/src/wuserver.c.o
[ 66%] Linking C executable wuserver
CMakeFiles/wuserver.dir/src/wuserver.c.o: In function `main':
[ 66%] Built target wuserver
Scanning dependencies of target wuclient
[ 83%] Building C object CMakeFiles/wuclient.dir/src/wuclient.c.o
[100%] Linking C executable wuclient
[100%] Built target wuclient
```
And then we have our three target executables: `version`, `wuclient`, and `wuserver`
