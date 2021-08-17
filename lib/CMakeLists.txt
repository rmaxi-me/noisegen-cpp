
add_library(
        libpengen
        src/Generator.cpp include/perlin-noise-generator/Generator.hpp
        src/Random.cpp include/perlin-noise-generator/Random.hpp
        src/Settings.cpp include/perlin-noise-generator/Settings.hpp
        src/ScopedProfiler.cpp include/perlin-noise-generator/ScopedProfiler.hpp
        src/Exception.cpp include/perlin-noise-generator/Exception.hpp
)
target_include_directories(libpengen PRIVATE include/perlin-noise-generator)

if (UNIX)
    set_target_properties(
            libpengen
            PROPERTIES
            PREFIX ""
    )
endif ()

