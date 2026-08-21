cmake_minimum_required(VERSION 3.20)

project(advanced_c_playground
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

enable_testing()

# ---------------------------------
# Libraries
# ---------------------------------

add_library(dynamic_array
    src/dynamic_array.c
)

target_include_directories(dynamic_array
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

add_library(linked_list
    src/linked_list.c
)

target_include_directories(linked_list
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

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

add_library(queue
    src/queue.c
)

target_include_directories(queue
    PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
)

# ---------------------------------
# Tests
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
# Compiler warnings
# ---------------------------------

if(MSVC)

    target_compile_options(dynamic_array PRIVATE /W4)
    target_compile_options(linked_list PRIVATE /W4)
    target_compile_options(stack PRIVATE /W4)
    target_compile_options(queue PRIVATE /W4)

    target_compile_options(test_dynamic_array PRIVATE /W4)
    target_compile_options(test_linked_list PRIVATE /W4)
    target_compile_options(test_stack PRIVATE /W4)
    target_compile_options(test_queue PRIVATE /W4)

else()

    target_compile_options(dynamic_array PRIVATE -Wall -Wextra -Werror)
    target_compile_options(linked_list PRIVATE -Wall -Wextra -Werror)
    target_compile_options(stack PRIVATE -Wall -Wextra -Werror)
    target_compile_options(queue PRIVATE -Wall -Wextra -Werror)

    target_compile_options(test_dynamic_array PRIVATE -Wall -Wextra -Werror)
    target_compile_options(test_linked_list PRIVATE -Wall -Wextra -Werror)
    target_compile_options(test_stack PRIVATE -Wall -Wextra -Werror)
    target_compile_options(test_queue PRIVATE -Wall -Wextra -Werror)

endif()