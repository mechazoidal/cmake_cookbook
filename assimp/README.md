# Open Asset Import Library
## assimp

Assimp is an example of a well-meaning complicated import. The project maintains their own cmake system, but it is not usually installed directly to a packaging system.

Since the library is special-purpose enough to assume it will not be present, we use the excellent DownloadProject cmake module to acquire the source at build-time, then incorporate it into our cmake build using `add_subdirectory()`

## Library requirements:
### Linux:
  - freeglut3-dev
  - libxmu-dev

## Known bugs
On OSX, if minizip is already installed on the system, linking to minizip during build finish may fail. 
This is due to assimp using outdated pkg-config macros from OGRE, which will automatically pick up the wrong link directory due to a [pkg-config quirk in cmake](https://cmake.org/Bug/view.php?id=15804)
