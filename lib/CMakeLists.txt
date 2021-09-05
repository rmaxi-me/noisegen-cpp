
add_library(
        libpengen
        src/Generator.cpp include/perlin-noise-generator/Generator.hpp
        src/Random.cpp include/perlin-noise-generator/Random.hpp
        src/Settings.cpp include/perlin-noise-generator/Settings.hpp
        src/ScopedProfiler.cpp include/perlin-noise-generator/ScopedProfiler.hpp
        src/Exception.cpp include/perlin-noise-generator/Exception.hpp
        include/perlin-noise-generator/PengenCImg.hpp
)
target_include_directories(libpengen PRIVATE include/perlin-noise-generator)

if (PENGEN_PCH AND NOT ${CMAKE_VERSION} VERSION_LESS "3.16")
    target_precompile_headers(
            libpengen PUBLIC
            <CImg.h>
    )
endif ()

if (UNIX)
    set_target_properties(
            libpengen
            PROPERTIES
            PREFIX ""
    )
endif ()

