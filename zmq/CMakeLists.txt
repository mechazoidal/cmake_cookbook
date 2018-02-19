cmake_minimum_required(VERSION 2.8)

project(zmq_example)

# Add our project-specific Modules directory to the cmake module search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# With our project module set, find the library in the system.
find_package(ZeroMQ)

# An example of echoing a variable set by find_package
message(STATUS "ZeroMQ version: ${ZeroMQ_VERSION}")

# include_directories applies to ALL following targets once set.
include_directories(include
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

# Link our executables.
# Note that libraries may be linked to a target immediately after declaring it
# with add_executable, but I prefer to keep them in one section.
target_link_libraries(wuclient
  ${ZeroMQ_LIBRARIES}
)

target_link_libraries(wuserver
  ${ZeroMQ_LIBRARIES}
)

target_link_libraries(version
  ${ZeroMQ_LIBRARIES}
)
