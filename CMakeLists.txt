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


#if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
#
#    # Set run-time library building default to static. This only applies to MSVS compiler,
#    # since all google units have default MT.
#    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
#
#    # If windows, set find_library_suffixes to both static and shared(.lib; .dll)
#    set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_STATIC_LIBRARY_SUFFIX})
#
#endif()


# Add include directories so the test routines can pick up the library contents
include_directories(source)


# Add the source and test directories
add_subdirectory(source)
add_subdirectory(test)
