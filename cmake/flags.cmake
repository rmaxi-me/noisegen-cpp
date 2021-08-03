if (UNIX)
    if (NOT APPLE)
        link_libraries(pthread stdc++fs)
    endif ()
    add_compile_options(-Wall -Wextra -Weffc++)
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_compile_definitions(DEBUG=1)
else ()
    add_compile_definitions(RELEASE=1)
endif ()

if (${RELEASE_WITH_PROFILER})
    add_compile_definitions(RELEASE_WITH_PROFILER=1)
endif ()

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

    #    add_link_options(/ignore:4099)
    #    link_libraries(legacy_stdio_definitions)
endif ()
