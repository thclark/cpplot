
# The cpr dependency uses curl. If there's a system curl, use it (faster)
find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()

# Add boost as multithreaded
set(Boost_USE_MULTITHREADED TRUE)

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

# Include headers from the third party libraries
target_include_directories(cpplot PUBLIC ${CONAN_INCLUDE_DIRS})

# Build the executable wrapping the library and generating the example figures
add_executable(cpplot-examples main.cpp)

# Link against the third party libraries, and link cpplot-examples against cpplot
target_link_libraries(cpplot ${CONAN_LIBS})
target_link_libraries(cpplot-examples cpplot ${CONAN_LIBS})

# Install the library
message("-- Install directory is " ${CMAKE_INSTALL_PREFIX})
install (TARGETS cpplot DESTINATION lib)
install (FILES cpplot.h DESTINATION include)
