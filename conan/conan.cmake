# Conan CMake setup

macro(run_conan)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan/conan.cmake)

    conan_add_remote(NAME bincrafters URL https://api.bintray.com/conan/bincrafters/public-conan)

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        set(_GLIBCXX_USE_CXX11_ABI)
    endif ()

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
        # Fixes build issue with conan on macOS by forcing cpp standard
        # I don't know why it happens as it shouldn't, but this should be working consistently.
        set(PENGEN_APPLE_CXXSTD "")
    else ()
        set(PENGEN_APPLE_CXXSTD "")
    endif ()

    conan_cmake_run(
        # options
        BASIC_SETUP
        NO_OUTPUT_DIRS
        CMAKE_TARGETS
        TARGETS
        # oneValueArgs
        INSTALL_FOLDER ${CMAKE_BINARY_DIR}/conan
        CONANFILE conan/conanfile.txt
        # multiValueArgs
        BUILD missing
        INSTALL_ARGS
        ${PENGEN_APPLE_CXXSTD}
        REQUIRES ${CONAN_EXTRA_REQUIRES}
        OPTIONS ${CONAN_EXTRA_OPTIONS}
    )
endmacro()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_BINARY_DIR}/conan")
