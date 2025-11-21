cmake_minimum_required(VERSION 3.10)
project(test_utility CXX)

add_executable(test_utility main.cpp)

target_link_libraries(test_utility PRIVATE process_lib)

target_compile_definitions(test_utility
    PRIVATE
        DUMMY_APP_PATH="$<TARGET_FILE:dummy_app>"
)
