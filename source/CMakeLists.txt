
# Build cpr dependency (a git submodule)
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

# Add nlohmann::json header library dependency (a git submodule)
set(JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/json/src PARENT_SCOPE)
include_directories(${JSON_INCLUDE_DIRS})

# Add boost
set(Boost_USE_MULTITHREADED TRUE)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

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
    find_package (Eigen REQUIRED)
    include_directories(${EIGEN_INCLUDE_DIRS})
endif ()


# Add the library
set(SOURCE_FILES
        exceptions.h
        cpplot.h
        cpplot.cpp
        main.cpp
        plot_types/bar.h
        plot_types/scatter.h
        plot_types/surface.h
        online.h
        eigen.h
        layout.h)
add_library(cpplot STATIC ${SOURCE_FILES})
message("-- Source files for library cpplot: ${SOURCE_FILES}")


target_include_directories(cpplot PUBLIC ${GLOG_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})


# Build the executable wrapping the library and generating the example figures
add_executable(cpplot-examples main.cpp)


# TODO remove this horrible windows bodge
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(cpplot ${Boost_LIBRARIES} ${CPR_LIBRARIES} Eigen3::Eigen glog::glog)
    target_link_libraries(cpplot-examples cpplot ${Boost_LIBRARIES} ${CPR_LIBRARIES} Eigen3::Eigen glog::glog)
else ()
    target_link_libraries(cpplot ${EIGEN_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES} ${CPR_LIBRARIES})
    target_link_libraries(cpplot-examples cpplot ${EIGEN_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES} ${CPR_LIBRARIES})
endif ()

message("-- Install directory is " ${CMAKE_INSTALL_PREFIX})
install (TARGETS cpplot DESTINATION lib)
install (FILES cpplot.h json/single_include/nlohmann/json.hpp DESTINATION include)
