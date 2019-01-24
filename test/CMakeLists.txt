
# Add boost for stacktrace and filesystem dependency
find_package(Boost REQUIRED COMPONENTS filesystem system)
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
target_link_libraries(cpplot_test ${GTEST_BOTH_LIBRARIES})

# Link the third party libraries
target_link_libraries(cpplot_test ${Boost_LIBRARIES})

# Link the library to test
target_link_libraries(cpplot_test cpplot)
