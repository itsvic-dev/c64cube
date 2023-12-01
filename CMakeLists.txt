cmake_minimum_required(VERSION 3.18)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to MinSizeRel")
  set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type (default MinSizeRel)" FORCE)
endif()

set(LLVM_MOS_PLATFORM c64)
find_package(llvm-mos-sdk REQUIRED)
project(c64fun)

add_library(
  cubecore STATIC
  point.cpp fixed.cpp
  fixedmath.cpp
)

target_compile_options(cubecore PUBLIC -Os -Wall -Werror)

add_executable(c64cube
  main.cpp render.cpp
)

target_link_libraries(c64cube cubecore)


option(ENABLE_TEST "Enable test program." OFF)
if(ENABLE_TEST)
  add_executable(cubetesting
    test.cpp
  )
  target_link_libraries(cubetesting cubecore)
endif()
