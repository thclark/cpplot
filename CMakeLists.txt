cmake_minimum_required(VERSION 3.6)
project(cpplot)


# Add cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Set make options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE ON)


# Add third party tools required by conan
message("-- Adding dependencies with conan. Make sure you've called `conan install . --install-folder ${CMAKE_BINARY_DIR}`")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# Add include directories so the test routines can pick up the library contents
include_directories(source)


# Add the source and test directories
add_subdirectory(source)
add_subdirectory(test)
