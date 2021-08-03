cmake_minimum_required(VERSION 3.10)
project(perlin-noise-generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

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
