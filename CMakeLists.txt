cmake_minimum_required(VERSION 3.20)

project(advanced_c_playground
    VERSION 1.0
    LANGUAGES C
)

# ---------------------------------
# C Standard
# ---------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ---------------------------------
# Testing
# ---------------------------------

enable_testing()

# =================================
# Libraries
# =================================

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
# Queue
# ---------------------------------

add_library(queue
    src/queue.c
)

target_include_directories(queue
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

# ---------------------------------
# Circular Buffer
# ---------------------------------

add_library(circular_buffer
    src/circular_buffer.c
)

target_include_directories(circular_buffer
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

# =================================
# Test Executables
# =================================

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
# Queue Tests
# ---------------------------------

add_executable(test_queue
    tests/test_queue.c
)

target_link_libraries(test_queue
    PRIVATE
        queue
)

add_test(
    NAME queue_tests
    COMMAND test_queue
)

# ---------------------------------
# Circular Buffer Tests
# ---------------------------------

add_executable(test_circular_buffer
    tests/test_circular_buffer.c
)

target_link_libraries(test_circular_buffer
    PRIVATE
        circular_buffer
)

add_test(
    NAME circular_buffer_tests
    COMMAND test_circular_buffer
)

# =================================
# Compiler Warnings
# =================================

if(MSVC)

    target_compile_options(dynamic_array PRIVATE /W4)
    target_compile_options(linked_list PRIVATE /W4)
    target_compile_options(stack PRIVATE /W4)
    target_compile_options(queue PRIVATE /W4)
    target_compile_options(circular_buffer PRIVATE /W4)

    target_compile_options(test_dynamic_array PRIVATE /W4)
    target_compile_options(test_linked_list PRIVATE /W4)
    target_compile_options(test_stack PRIVATE /W4)
    target_compile_options(test_queue PRIVATE /W4)
    target_compile_options(test_circular_buffer PRIVATE /W4)

else()

    target_compile_options(dynamic_array
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(linked_list
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(stack
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(queue
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(circular_buffer
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(test_dynamic_array
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(test_linked_list
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(test_stack
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(test_queue
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

    target_compile_options(test_circular_buffer
        PRIVATE
            -Wall
            -Wextra
            -Werror
    )

endif()