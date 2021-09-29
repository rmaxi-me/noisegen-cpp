cmake_minimum_required(VERSION 3.10)
project(noisegen-cpp)

if (NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 17)
endif ()

if (NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)

    message(WARNING "CMAKE_BUILD_TYPE undefined. Defaulting to Release.")
endif ()

include(conan/conan.cmake)
run_conan()
link_directories(${CONAN_LIB_DIRS})
link_libraries(${CONAN_LIBS})
include_directories(SYSTEM "${CONAN_INCLUDE_DIRS}")

include(cmake/flags.cmake)

option(NOISEGEN_BUILD_CLI "Build CLI" ON)
option(NOISEGEN_BUILD_GUI "Build GUI" ON) # soon™️

option(NOISEGEN_WITH_PROFILER "Enable scoped profiler" OFF)
# option(NOISEGEN_BUILD_SHARED_LIB "Build Shared Library" OFF) # TODO: implement this

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

if (${NOISEGEN_BUILD_CLI})
    add_subdirectory(cli)
endif ()
