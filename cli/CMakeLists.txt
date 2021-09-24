add_executable(
        pengencli
        src/Main.cpp
)
target_link_libraries(pengencli PUBLIC pengen)
target_include_directories(pengencli SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/vendor/argparse/include)

target_precompile_headers(pengencli REUSE_FROM pengen)
