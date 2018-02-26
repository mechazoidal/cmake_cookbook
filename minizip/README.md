# Minizip
[Minizip](http://www.winimage.com/zLibDll/minizip.html) is a simple ZIP-file library, using zlib. zlib is part of almost every OS distribution, while minizip is not. Unlike other CMake-ready libraries, Minizip packages come with pkg-config files, so the `find_package` call will not work. Here we show how to use pkg-config from CMake, along with why it's not preferred.

## Requirements

Linux:
  - zlib1g-dev
  - libminizip-dev

OSX/BSD:
  - minizip
  - zlib

## Project layout

```
minizip
|-- CMakeLists.txt
|-- README.md
`-- src
    |-- miniunzip.c
    `-- minizip.c
```

## CMakeLists walkthrough
Define our project and CMake version. Versions prior to 3.1 can have random bugs when dealing directly with pkg-config, so we enforce the minimum version here.
```
cmake_minimum_required(VERSION 3.1)
project(test_minizip)
```

CMake ships a FindZLIB.cmake file, so request it here. As a potential quirk, note that `find_package(zlib)` would also work on OSX/BSD systems, but not on Linux, as it's case-sensitive. It's safer just to request the uppercase version to avoid confusion.
```
find_package(ZLIB)
```

Since we know we are going to need pkg-config, request the built-in PkgConfig CMake package
```
find_package(PkgConfig)
```
There are two major ways to find pkg-config modules: `pkg_search_module`, and `pkg_check_modules`. They have slightly differing syntaxes. I prefer to use `pkg_check_modules` to enforce the requirement.
```
pkg_check_modules(UNZIP minizip)
```

Because we called `pkg_check_modules` with a prefix(`UNZIP`), the minizip variables will be bound to that prefix. (Look in `<build_dir>/CMakeCache.txt` to see them all, searching for "UNZIP_")

As usual, include minizip/include directory, and the directory specified by the minizip pkg-config
```
include_directories(include
  ${UNZIP_INCLUDEDIR}
)
```

Since we didn't use `find_package`, we have to include the actual library flags manually, which is what `find_library` is for. `find_package` will automatically do this and bind the flags to `<prefix>_LIBRARIES`, which is another good reason to prefer `find_package`.
```
find_library(minizip_LIBRARY minizip)
```

Now we can add our executables. We have two separate source files which compile to an executable each: minizip, and miniunzip. 
```
add_executable(minizip
  src/minizip.c
)
add_executable(miniunzip
  src/miniunzip.c
)
```

Each executable needs to be linked separately. Note that by using `find_library` the minizip flags are now in the `minizip_LIBRARY` variable, as opposed to zlib which gets a \_LIBRARIES suffix(again, thanks to `find_package`).
```
target_link_libraries(minizip
  ${ZLIB_LIBRARIES}
  ${minizip_LIBRARY}
)
target_link_libraries(miniunzip
  ${ZLIB_LIBRARIES}
  ${minizip_LIBRARY}
)
```

## Use
Let's make our build dir and run cmake like usual:
```
$ mkdir build
$ cd build
$ cmake ..
```

After the usual compiler detection, you should see this output:
```
-- Found ZLIB: /usr/lib/libz.so.5.0 (found version "1.2.3") 
-- Found PkgConfig: /usr/bin/pkg-config (found version "0.27.1") 
-- Checking for module 'minizip'
--   Found minizip, version 1.2.11
```
(location and version numbers will vary on your system)

Then we can execute:
```
$ make
$ minizip test.zip ../src/minizip.c
$ file test.zip
```
