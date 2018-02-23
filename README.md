
mkdir build
cmake ..
<build system invocation>

This is what's called an "out-of-source" build, and I encourage its use with cmake. There are two main advantages in cmake:
  - when creating/debugging a CMakeLists.txt file, it's easy to remove the directory and not have to worry about any lingering CMake variables(subsequent cmake/make calls will NOT remove variables you might have set in previous versions of your CMakeLists.txt!)
  - it's easy to grep through the directory to find out what a 3rd-party library is trying to do while debugging a CMakeLists.txt file


Linux:
  - build-essential
  - git
  - cmake
  - pkg-config
  - libglew-dev
  - libglfw3-dev

Tested on:
  - OpenBSD 6.2
  - OSX 10.11 w/ Macports 2.4.2
  - Debian stretch
