cmake_minimum_required(VERSION 3.16)

project(
  tinylog
  VERSION 0.0.1
  DESCRIPTION "Minimal, header-only logging library."
  HOMEPAGE_URL "https://github.com/abidanBrito/tinylog"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TINYLOG_BUILD_EXAMPLES "Build example programs" ON)

# Header-only library
add_library(tinylog INTERFACE)
add_library(tinylog::tinylog ALIAS tinylog)

target_include_directories(tinylog INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Thread support
find_package(Threads REQUIRED)
target_link_libraries(tinylog INTERFACE Threads::Threads)

# Print configuration
message(STATUS "=======================================")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "=======================================")

# Examples
if(TINYLOG_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
