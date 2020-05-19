cmake_minimum_required(VERSION 3.13...3.16)
include(CMakePrintHelpers)

project(zmq_example VERSION 1.0 LANGUAGES C)

# With our project module set, find the library in the system.
find_package(ZeroMQ)

# An example of echoing a variable set by find_package
message(STATUS "ZeroMQ version: ${ZeroMQ_VERSION}")

# include_directories applies to ALL following targets once set.
include_directories(
  ${ZeroMQ_INCLUDE_DIR}
)

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
  ${ZeroMQ_INCLUDE_DIR}
)
target_include_directories(wuserver
  PUBLIC
  include
  ${ZeroMQ_INCLUDE_DIR}
)
target_include_directories(version
  PUBLIC
  include
  ${ZeroMQ_INCLUDE_DIR}
)

# Link our executables.
# Note that libraries may be linked to a target immediately after declaring it
# with add_executable, but I prefer to keep them in one section.
target_link_libraries(wuclient
  PRIVATE
  zmq
)

target_link_libraries(wuserver
  PRIVATE
  zmq
)

target_link_libraries(version
  PRIVATE
  zmq
)
cmake_print_properties(
    TARGETS wuclient
    PROPERTIES LINK_LIBRARIES INCLUDE_DIRECTORIES
)
