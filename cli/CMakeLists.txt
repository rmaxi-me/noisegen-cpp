add_executable(
        noisegencli
        src/Main.cpp
)
target_link_libraries(noisegencli PUBLIC noisegen)
target_include_directories(noisegencli SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/vendor/argparse/include)
