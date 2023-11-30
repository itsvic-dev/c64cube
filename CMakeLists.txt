cmake_minimum_required(VERSION 3.18)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to MinSizeRel")
  set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type (default MinSizeRel)" FORCE)
endif()

set(LLVM_MOS_PLATFORM c64)
find_package(llvm-mos-sdk REQUIRED)

project(c64fun)
add_executable(c64fun
  main.cpp render.cpp
  point.cpp
)
target_compile_options(c64fun PUBLIC -Os)
