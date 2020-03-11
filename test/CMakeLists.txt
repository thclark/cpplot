
# Add boost for stacktrace and filesystem dependency
set(Boost_USE_MULTITHREADED TRUE)
find_package(Boost REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIR})

# List the unit test files
set(UNIT_TEST_SOURCE_FILES
        unit/cpplot_test.cpp
        unit/main_test.cpp
        )

# Include google test
enable_testing()

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . RESULT_VARIABLE result WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build . RESULT_VARIABLE result WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)
include_directories("${gtest_SOURCE_DIR}/include")

# The unit test executable
add_executable(cpplot_test ${UNIT_TEST_SOURCE_FILES})

# Link the google test libraries
target_link_libraries(cpplot_test gtest gtest_main)

# Link the third party libraries
target_link_libraries(cpplot_test ${Boost_LIBRARIES})

# Link the library to test
target_link_libraries(cpplot_test cpplot)
