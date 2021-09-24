cmake_minimum_required(VERSION 3.16)
project(perlin-noise-generator)

if (NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 17)
endif ()

if (NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)

    message(WARNING "CMAKE_BUILD_TYPE undefined. Defaulting to Release.")
endif ()

include(cmake/flags.cmake)

option(PENGEN_BUILD_CLI "Build CLI" ON)
option(PENGEN_BUILD_GUI "Build GUI" ON) # soon™️

option(PENGEN_WITH_PROFILER "Enable scoped profiler" OFF)
# option(PENGEN_BUILD_SHARED_LIB "Build Shared Library" ON) # TODO: implement this

if (WIN32 OR WIN64)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/")
else ()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()

add_subdirectory(lib)
include_directories(lib/include)

if (${PENGEN_BUILD_CLI})
    add_subdirectory(cli)
endif ()
