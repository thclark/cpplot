cmake_minimum_required(VERSION 3.6)
project(cpplot)


# Add cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Set make options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE ON)


# Add directories where third party tools exist
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/../thirdparty)
message("-- Defined THIRD_PARTY_DIR: ${THIRD_PARTY_DIR}")


if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")

    # Set run-time library building default to static. This only applies to MSVS compiler,
    # since all google units have default MT.
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    # If windows, set find_library_suffixes to both static and shared(.lib; .dll)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_STATIC_LIBRARY_SUFFIX})

    # Set variables for the embedded FIND_GTEST function.
    set(GTEST_ROOT ${THIRD_PARTY_DIR}/googletest/googletest)
    set (GTEST_MSVC_SEARCH MT)
    message("-- Defined GTEST_ROOT: ${GTEST_ROOT}")

endif()


# Add include directories so the test routines can pick up the library contents
include_directories(source)


# Add the souce and test directories
add_subdirectory(source)
add_subdirectory(test)
