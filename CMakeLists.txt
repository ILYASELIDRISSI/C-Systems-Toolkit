cmake_minimum_required(VERSION 3.20)

project(advanced-c-playground
    VERSION 1.0
    LANGUAGES C
)

enable_testing()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(dynamic_array
    src/dynamic_array.c
)

target_include_directories(dynamic_array
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

add_executable(test_dynamic_array
    tests/test_dynamic_array.c
)

target_link_libraries(test_dynamic_array
    PRIVATE
        dynamic_array
)

add_test(
    NAME dynamic_array_tests
    COMMAND test_dynamic_array
)

if(MSVC)
    target_compile_options(dynamic_array PRIVATE /W4)
    target_compile_options(test_dynamic_array PRIVATE /W4)
else()
    target_compile_options(dynamic_array PRIVATE
        -Wall
        -Wextra
        -Werror
    )

    target_compile_options(test_dynamic_array PRIVATE
        -Wall
        -Wextra
        -Werror
    )
endif()