add_executable(
        noisegencli
        src/Main.cpp
)
target_link_libraries(noisegencli PUBLIC noisegen)
