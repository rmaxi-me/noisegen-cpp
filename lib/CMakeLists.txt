add_library(
        pengen
        src/Generator.cpp include/perlin-noise-generator/Generator.hpp
        src/Random.cpp include/perlin-noise-generator/Random.hpp
        src/Settings.cpp include/perlin-noise-generator/Settings.hpp
        src/ScopedProfiler.cpp include/perlin-noise-generator/ScopedProfiler.hpp
        src/Exception.cpp include/perlin-noise-generator/Exception.hpp
)
target_include_directories(pengen PRIVATE include/perlin-noise-generator)
target_include_directories(pengen SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/vendor/CImg)
