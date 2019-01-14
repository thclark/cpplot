
# Build cpr
set(CPR_DIR cpr)
if(WIN32)
    option(CMAKE_USE_OPENSSL "Use OpenSSL code. Experimental" OFF)
endif()
set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")
find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()
add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})

# Build json
set(JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/json/src PARENT_SCOPE)
#add_subdirectory(json)
include_directories(${JSON_INCLUDE_DIRS})

# Add boost
find_package(Boost 1.67.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Add Intel MKL dependency
set(MKL_MULTI_THREADED "1")
find_package(MKL REQUIRED)
include_directories(${MKL_INCLUDE_DIRS})

# Add Intel TBB dependency
set(TBB_INSTALL_DIR "${THIRD_PARTY_DIR}/tbb")
find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIRS})

# TODO Move to building gflags, glog, eigen and ceres-solver
# Nice tutorial on doing that in cmake is here:
# https://www.selectiveintellect.net/blog/2016/7/29/using-cmake-to-add-third-party-libraries-to-your-project-1

# The instructions for adding subdirectories in the gflags docs are helpful: https://gflags.github.io/gflags/

# Add the gflags dependency
set(gflags_DIR ${THIRD_PARTY_DIR}/gflags)
# TODO find/add the gflags package!

# Add the glog dependency
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(glog_DIR ${THIRD_PARTY_DIR}/glog/build)
    find_package (glog  REQUIRED NO_MODULE )
else ()
    find_package (glog  REQUIRED )
    include_directories(${GLOG_INCLUDE_DIRS})
endif ()

# Add the eigen3 dependency
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(Eigen3_DIR ${THIRD_PARTY_DIR}/eigen)
    MESSAGE("-- Defined Eigen3_DIR: ${Eigen3_DIR}")
    find_package (Eigen3 REQUIRED NO_MODULE)
else ()
    set(EIGEN_INCLUDE_DIR_HINTS "${THIRD_PARTY_DIR}/eigen")
    find_package (Eigen REQUIRED)
    include_directories(${EIGEN_INCLUDE_DIRS})
endif ()

# Add ceres-solver dependency
#set(Ceres_DIR ${THIRD_PARTY_DIR}/ceres-solver)
#MESSAGE("-- Defined ceres_DIR: ${ceres_DIR}")
#find_package (ceres REQUIRED NO_MODULE)
#include_directories(${CERES_INCLUDE_DIRS})

# Add the library
set(SOURCE_FILES
        exceptions.h
        figures.h
        figures.cpp
        main.cpp plot_types/bar.h plot_types/scatter.h plot_types/scatter.cpp online.h)
add_library(cpplot STATIC ${SOURCE_FILES})
message("-- Source files for library cpplot: ${SOURCE_FILES}")


target_include_directories(cpplot PUBLIC ${GLOG_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS} ${TBB_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${CPR_INCLUDE_DIRS} $JSON_INCLUDE_DIRS})


# Build the executable wrapping the library and generating the example figures
add_executable(cpplot-examples main.cpp)


# TODO remove this horrible windows bodge
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(cpplot ${MKL_LIBRARIES} ${TBB_LIBRARIES} ${Boost_LIBRARIES} ${CPR_LIBRARIES} Eigen3::Eigen glog::glog)
    target_link_libraries(cpplot-examples cpplot ${MKL_LIBRARIES} ${TBB_LIBRARIES} ${Boost_LIBRARIES} ${CPR_LIBRARIES} Eigen3::Eigen glog::glog)
else ()
    target_link_libraries(cpplot ${EIGEN_LIBRARIES} ${GLOG_LIBRARIES} ${TBB_LIBRARIES} ${Boost_LIBRARIES} ${CPR_LIBRARIES})
    target_link_libraries(cpplot-examples cpplot ${EIGEN_LIBRARIES} ${GLOG_LIBRARIES} ${TBB_LIBRARIES} ${Boost_LIBRARIES} ${CPR_LIBRARIES})
endif ()
