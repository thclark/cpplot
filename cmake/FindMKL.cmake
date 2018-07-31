# Find intel MKL libraries

include(FindPackageHandleStandardArgs)
# Windows MKL and UNIX MKL have different install directories

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(INTEL_ROOT "${THIRD_PARTY_DIR}/mkl/compilers_and_libraries/windows")
    set(MKL_ROOT "${INTEL_ROOT}/mkl")
    find_path(MKL_INCLUDE_DIRS mkl.h PATHS ${MKL_ROOT}/include)
    set(MKL_LIBRARY_DIRS "${MKL_ROOT}/lib/intel64" "${INTEL_ROOT}/compiler/lib/intel64")
    # MKL is composed by four layers: Interface, Threading, Computational and RTL. Alternatively the single dynamic library can be used:
    #find_library(MKL_LIBRARY mkl_rt PATHS ${MKL_ROOT}/lib/)
    #set(MKL_MINIMAL_LIBRARY ${MKL_LIBRARY})
    #MESSAGE("MKL Single dynamic library (MKL_MINIMAL_LIBRARY) : ${MKL_MINIMAL_LIBRARY}")

    # Interface layer
    set(MKL_INTERFACE_LIBNAME mkl_intel_lp64)
    find_library(MKL_INTERFACE_LIBRARY ${MKL_INTERFACE_LIBNAME} PATHS ${MKL_LIBRARY_DIRS})

    # Threading layer
    if(${MKL_MULTI_THREADED})
        set(MKL_THREADING_LIBNAME mkl_intel_thread)
    else()
        set(MKL_THREADING_LIBNAME mkl_sequential)
    endif()
    #find_library(MKL_THREADING_LIBRARY ${MKL_THREADING_LIBNAME} PATHS ${MKL_ROOT}/lib/) # Doesn't work! Loads the sequential!!!
    find_library(TL ${MKL_THREADING_LIBNAME} PATHS ${MKL_LIBRARY_DIRS})
    set(MKL_THREADING_LIBRARY ${TL})

    # Computational layer
    find_library(MKL_CORE_LIBRARY mkl_core PATHS ${MKL_LIBRARY_DIRS})

    # RTL layer
    set(MKL_RTL_LIBNAME iomp5md)
    find_library(MKL_RTL_LIBRARY NAMES libiomp5md.lib PATHS  ${MKL_LIBRARY_DIRS})

# UNIX systems
else()
    set(INTEL_ROOT "/opt/intel")
    set(MKL_ROOT "${INTEL_ROOT}/mkl")
    find_path(MKL_INCLUDE_DIRS mkl.h PATHS ${MKL_ROOT}/include)
    set(MKL_LIBRARY_DIRS "${MKL_ROOT}/lib/" "${INTEL_ROOT}/lib")

    # Add other intel includes on systems where they appear (e.g. win32)
    find_path(INTEL_INCLUDE_DIR omp.h PATHS ${INTEL_ROOT}/include)
    if(INTEL_INCLUDE_DIR)
    MESSAGE("Adding INTEL_INCLUDE_DIR : ${INTEL_INCLUDE_DIR}")
    set(MKL_INCLUDE_DIRS ${MKL_INCLUDE_DIRS} ${INTEL_INCLUDE_DIR})
    # Interface layer
    set(MKL_INTERFACE_LIBNAME mkl_intel)
    find_library(MKL_INTERFACE_LIBRARY ${MKL_INTERFACE_LIBNAME} PATHS ${MKL_ROOT}/lib/)
    endif()
    # Threading layer
    if(${MKL_MULTI_THREADED})
        set(MKL_THREADING_LIBNAME mkl_intel_thread)
    else()
        set(MKL_THREADING_LIBNAME mkl_sequential)
    endif()
    #find_library(MKL_THREADING_LIBRARY ${MKL_THREADING_LIBNAME} PATHS ${MKL_ROOT}/lib/) # Doesn't work! Loads the sequential!!!
    find_library(TL ${MKL_THREADING_LIBNAME} PATHS ${MKL_ROOT}/lib/)
    set(MKL_THREADING_LIBRARY ${TL})

    # Computational layer
    find_library(MKL_CORE_LIBRARY mkl_core PATHS ${MKL_ROOT}/lib/)

    # RTL layer
    set(MKL_RTL_LIBNAME iomp5)
    find_library(MKL_RTL_LIBRARY ${MKL_RTL_LIBNAME} PATHS ${INTEL_ROOT}/lib)
endif()



# Handle the QUIETLY and REQUIRED arguments and set MKL_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(MKL DEFAULT_MSG MKL_INCLUDE_DIRS MKL_LIBRARY_DIRS)

if(MKL_FOUND)
    MESSAGE("-- Found Intel Math Kernel Library (MKL)")
    set(MKL_LIBRARIES ${MKL_INTERFACE_LIBRARY} ${MKL_THREADING_LIBRARY} ${MKL_CORE_LIBRARY} ${MKL_RTL_LIBRARY})
endif()

MESSAGE("-- Defined MKL_INCLUDE_DIRS: ${MKL_INCLUDE_DIRS}")
MESSAGE("-- Defined MKL LIBRARY_DIRS: ${MKL_LIBRARY_DIRS}")
MESSAGE("-- Defined MKL_LIBRARIES: ${MKL_LIBRARIES}")
