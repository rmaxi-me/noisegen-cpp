
add_executable(
        pengen
        src/Main.cpp
)
target_link_libraries(pengen PUBLIC libpengen)

if (PENGEN_PCH AND NOT ${CMAKE_VERSION} VERSION_LESS "3.16")
    target_precompile_headers(pengen REUSE_FROM libpengen)
endif ()
