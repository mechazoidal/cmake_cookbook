# CMake Cookbook
This is a collection of subprojects showing various facets of [CMake](https://cmake.org). It started out as a tool-evaluation repository, so the libraries reflect my interests.

## Use
Each project has a README detailing sub-requirements, showing the project layout, and walking through the CMakeLists.txt files. 

Generally for each I encourage this usage:
```
$ mkdir build
$ cmake ..
$ <build system invocation>
```

This is what's called an "out-of-source" build, and I encourage its use with CMake. There are a main advantages in CMake:
  - when creating/debugging a CMakeLists.txt file, it's easy to remove the directory and not have to worry about any lingering CMake variables(subsequent cmake/make calls will NOT remove variables you might have set in previous versions of your CMakeLists.txt!)
  - it's easy to grep through the directory to find out what a 3rd-party library is trying to do while debugging a CMakeLists.txt file
  - There will be a LOT of files generated, and it's easier to have a `build/*` directive in your SCM ignore file, vs. manually cleaning out after a build.

Don't forget there are many ways of running CMake beyond the standard CLI invocation! See the official [Running CMake](https://cmake.org/runningcmake/) for more.

Tested on:
  - OpenBSD 6.2
  - OSX 10.11 w/ Macports 2.4.2
  - Debian stretch

I don't currently have access to a Windows installation, so I'd welcome anyone who can test these. Theoretically there shouldn't be much of an issue, outside of needing the dependencies installed.

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

## TODO
