if (UNIX)
    if (NOT APPLE)
        link_libraries(pthread stdc++fs tbb)
        add_compile_definitions(TBB_SUPPRESS_DEPRECATED_MESSAGES=1) # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=101228
    endif ()

    add_compile_options(-Wall -Wextra)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-Weffc++)
    endif ()
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_definitions(PENGEN_HAS_EXEC_POLICIES=0)
else ()
    add_compile_definitions(PENGEN_HAS_EXEC_POLICIES=1)
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_compile_definitions(DEBUG=1)
else ()
    add_compile_definitions(RELEASE=1)
endif ()

if (${PENGEN_WITH_PROFILER})
    add_compile_definitions(PENGEN_WITH_PROFILER=1)
else ()
    add_compile_definitions(PENGEN_WITH_PROFILER=0)
endif ()

if (MSVC)
    add_link_options(/ignore:4099)
    #    link_libraries(legacy_stdio_definitions)
endif ()

add_compile_definitions(cimg_display=0) # Won't need to display anything through CImg
