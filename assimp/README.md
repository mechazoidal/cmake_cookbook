# Open Asset Import Library
## assimp

Assimp is an example of a well-meaning complicated import. The project maintains their own cmake system, but it is not usually installed directly to a packaging system.

Since the library is special-purpose enough to assume it will not be present, we use the excellent DownloadProject cmake module to acquire the source at build-time, then incorporate it into our cmake build using `add_subdirectory()`
