cmake_minimum_required(VERSION 3.13...3.16)
include(CMakePrintHelpers)

project(zmq_example VERSION 1.0 LANGUAGES C)

# With our project module set, find the library in the system.
find_package(ZeroMQ 4.3 CONFIG)

# If the platform's zeromq package doesn't have a proper cmake config but is known to pkg-config,
# import it from there.
if(NOT ZeroMQ_DIR)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(ZeroMQ REQUIRED IMPORTED_TARGET libzmq)
endif()

# An example of echoing a variable set by find_package/pkg_check_modules
message(STATUS "ZeroMQ version: ${ZeroMQ_VERSION}")

# Declare our executable targets and their sources
add_executable(wuclient
  src/wuclient.c
)

add_executable(wuserver
  src/wuserver.c
)

add_executable(version
  src/version.c
)

target_include_directories(wuclient
  PUBLIC
  include
  ${ZeroMQ_INCLUDE_DIRS}
)
target_include_directories(wuserver
  PUBLIC
  include
  ${ZeroMQ_INCLUDE_DIRS}
)
target_include_directories(version
  PUBLIC
  include
  ${ZeroMQ_INCLUDE_DIRS}
)

# Link our executables.
# Since the target name may vary depending on if PkgConfig was used,
# we cover all possibilities using generator expressions.
target_link_libraries(wuclient
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:libzmq>
  $<TARGET_NAME_IF_EXISTS:PkgConfig::ZeroMQ>
)

target_link_libraries(wuserver
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:libzmq>
  $<TARGET_NAME_IF_EXISTS:PkgConfig::ZeroMQ>
)

target_link_libraries(version
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:libzmq>
  $<TARGET_NAME_IF_EXISTS:PkgConfig::ZeroMQ>
)

cmake_print_properties(
    TARGETS wuclient
    PROPERTIES LINK_LIBRARIES INCLUDE_DIRECTORIES
)
