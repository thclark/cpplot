
# Add boost for stacktrace and filesystem dependency
find_package(Boost 1.67.0 REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIR})

# List the unit test files
set(UNIT_TEST_SOURCE_FILES
        unit/figures_test.cpp
        unit/main_test.cpp
        )

# Include google test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# The unit test executable
add_executable(cpplot_test ${UNIT_TEST_SOURCE_FILES})

# Link the google test libraries
target_link_libraries(cpplot_test)
target_link_libraries(cpplot_test cpplot ${GTEST_BOTH_LIBRARIES} ${Boost_LIBRARIES})
