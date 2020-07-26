
# Add boost for stacktrace and filesystem dependency
# TODO Resolve whether boost (now installed with conan) will actually work as multithreaded like this
set(Boost_USE_MULTITHREADED TRUE)
#find_package(Boost REQUIRED COMPONENTS filesystem system)
#include_directories(${Boost_INCLUDE_DIR})

# List the unit test files
set(UNIT_TEST_SOURCE_FILES
        unit/cpplot_test.cpp
        unit/main_test.cpp)

# Include google test
enable_testing()

# The unit test executable
add_executable(cpplot_test ${UNIT_TEST_SOURCE_FILES})

# Link the google test and boost libraries
target_link_libraries(cpplot_test ${CONAN_LIBS})

# Link the library to test
target_link_libraries(cpplot_test cpplot)
