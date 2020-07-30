cmake_minimum_required(VERSION 3.6)
project(cpplot)


# Add cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Set make options
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Lets glog play more nicely with Windows
IF(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES)
endif()

# Add third party tools required by conan
message("-- Adding dependencies with conan. Make sure you've called `conan install . --install-folder ${CMAKE_BINARY_DIR}`")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# Add include directories so the test routines can pick up the library contents
include_directories(source)


# Add the source and test directories
add_subdirectory(source)
add_subdirectory(test)
