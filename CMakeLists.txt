cmake_minimum_required(VERSION 3.20)

project(advanced_c_playground
    VERSION 1.0
    LANGUAGES C
)

# ---------------------------------
# C standard
# ---------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ---------------------------------
# Testing
# ---------------------------------

enable_testing()

# ---------------------------------
# Dynamic Array
# ---------------------------------

add_library(dynamic_array
    src/dynamic_array.c
)

target_include_directories(dynamic_array
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

# ---------------------------------
# Linked List
# ---------------------------------

add_library(linked_list
    src/linked_list.c
)

target_include_directories(linked_list
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

# ---------------------------------
# Stack
# ---------------------------------

add_library(stack
    src/stack.c
)

target_include_directories(stack
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

target_link_libraries(stack
    PUBLIC
        dynamic_array
)

# ---------------------------------
# Dynamic Array Tests
# ---------------------------------

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

# ---------------------------------
# Linked List Tests
# ---------------------------------

add_executable(test_linked_list
    tests/test_linked_list.c
)

target_link_libraries(test_linked_list
    PRIVATE
        linked_list
)

add_test(
    NAME linked_list_tests
    COMMAND test_linked_list
)

# ---------------------------------
# Stack Tests
# ---------------------------------

add_executable(test_stack
    tests/test_stack.c
)

target_link_libraries(test_stack
    PRIVATE
        stack
)

add_test(
    NAME stack_tests
    COMMAND test_stack
)

# ---------------------------------
# Compiler warnings
# ---------------------------------

if(MSVC)

    target_compile_options(dynamic_array PRIVATE /W4)
    target_compile_options(linked_list PRIVATE /W4)
    target_compile_options(stack PRIVATE /W4)

    target_compile_options(test_dynamic_array PRIVATE /W4)
    target_compile_options(test_linked_list PRIVATE /W4)
    target_compile_options(test_stack PRIVATE /W4)

else()

    target_compile_options(dynamic_array PRIVATE
        -Wall
        -Wextra
        -Werror
    )

    target_compile_options(linked_list PRIVATE
        -Wall
        -Wextra
        -Werror
    )

    target_compile_options(stack PRIVATE
        -Wall
        -Wextra
        -Werror
    )

    target_compile_options(test_dynamic_array PRIVATE
        -Wall
        -Wextra
        -Werror
    )

    target_compile_options(test_linked_list PRIVATE
        -Wall
        -Wextra
        -Werror
    )

    target_compile_options(test_stack PRIVATE
        -Wall
        -Wextra
        -Werror
    )

endif()