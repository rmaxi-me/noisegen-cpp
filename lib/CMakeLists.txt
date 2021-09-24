add_library(
        noisegen
        src/Generator.cpp include/noisegen/Generator.hpp
        src/Random.cpp include/noisegen/Random.hpp
        src/Settings.cpp include/noisegen/Settings.hpp
        src/ScopedProfiler.cpp include/noisegen/ScopedProfiler.hpp
        src/Exception.cpp include/noisegen/Exception.hpp
)
target_include_directories(noisegen PRIVATE include/noisegen)
target_include_directories(noisegen SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/vendor/CImg)
