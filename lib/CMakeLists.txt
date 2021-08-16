
add_library(
        libpengen
        src/Generator.cpp include/perlin-noise-generator/Generator.hpp
)
target_include_directories(libpengen PRIVATE include/perlin-noise-generator)

if (UNIX)
    set_target_properties(
            libpengen
            PROPERTIES
            PREFIX ""
    )
endif ()

