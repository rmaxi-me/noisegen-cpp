cmake_minimum_required(VERSION 3.10)
project(perlin-noise-generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)

    message(WARNING "CMAKE_BUILD_TYPE undefined. Defaulting to Release.\nPossible values: [Debug, Release, MinSizeRel, RelWithDebInfo]")
endif ()

include(conan/conan.cmake)
run_conan()
link_directories(${CONAN_LIB_DIRS})
link_libraries(${CONAN_LIBS})
include_directories(SYSTEM "${CONAN_INCLUDE_DIRS}")

include(cmake/flags.cmake)

option(PNG_BUILD_EXECUTABLE "Build Executable" ON)
option(PNG_BUILD_SHARED_LIB "Build Shared Library" ON) # TODO: implement this

add_subdirectory(lib)
include_directories(lib/include)

if (${PNG_BUILD_EXECUTABLE})
    add_subdirectory(exe)
endif ()
