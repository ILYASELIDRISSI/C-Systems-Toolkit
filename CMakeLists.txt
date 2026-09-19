cmake_minimum_required(VERSION 3.20)

project(c_systems_toolkit
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

enable_testing()

function(enable_warnings target)
    if(MSVC)
        target_compile_options(${target}
            PRIVATE
                /W4
        )
    else()
        target_compile_options(${target}
            PRIVATE
                -Wall
                -Wextra
                -Werror
        )
    endif()
endfunction()

add_library(dynamic_array src/dynamic_array.c)
target_include_directories(dynamic_array PUBLIC ${PROJECT_SOURCE_DIR}/include)
enable_warnings(dynamic_array)

add_library(linked_list src/linked_list.c)
target_include_directories(linked_list PUBLIC ${PROJECT_SOURCE_DIR}/include)
enable_warnings(linked_list)

add_library(stack src/stack.c)
target_include_directories(stack PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(stack PUBLIC dynamic_array)
enable_warnings(stack)

add_library(queue src/queue.c)
target_include_directories(queue PUBLIC ${PROJECT_SOURCE_DIR}/include)
enable_warnings(queue)

add_library(circular_buffer src/circular_buffer.c)
target_include_directories(circular_buffer PUBLIC ${PROJECT_SOURCE_DIR}/include)
enable_warnings(circular_buffer)

add_library(hash_table src/hash_table.c)
target_include_directories(hash_table PUBLIC ${PROJECT_SOURCE_DIR}/include)
enable_warnings(hash_table)

add_library(binary_search_tree src/binary_search_tree.c)
target_include_directories(binary_search_tree PUBLIC ${PROJECT_SOURCE_DIR}/include)
enable_warnings(binary_search_tree)

add_library(memory_pool src/memory_pool.c)
target_include_directories(memory_pool PUBLIC ${PROJECT_SOURCE_DIR}/include)
enable_warnings(memory_pool)

add_executable(test_dynamic_array tests/test_dynamic_array.c)
target_link_libraries(test_dynamic_array PRIVATE dynamic_array)
enable_warnings(test_dynamic_array)
add_test(NAME dynamic_array_tests COMMAND test_dynamic_array)

add_executable(test_linked_list tests/test_linked_list.c)
target_link_libraries(test_linked_list PRIVATE linked_list)
enable_warnings(test_linked_list)
add_test(NAME linked_list_tests COMMAND test_linked_list)

add_executable(test_stack tests/test_stack.c)
target_link_libraries(test_stack PRIVATE stack)
enable_warnings(test_stack)
add_test(NAME stack_tests COMMAND test_stack)

add_executable(test_queue tests/test_queue.c)
target_link_libraries(test_queue PRIVATE queue)
enable_warnings(test_queue)
add_test(NAME queue_tests COMMAND test_queue)

add_executable(test_circular_buffer tests/test_circular_buffer.c)
target_link_libraries(test_circular_buffer PRIVATE circular_buffer)
enable_warnings(test_circular_buffer)
add_test(NAME circular_buffer_tests COMMAND test_circular_buffer)

add_executable(test_hash_table tests/test_hash_table.c)
target_link_libraries(test_hash_table PRIVATE hash_table)
enable_warnings(test_hash_table)
add_test(NAME hash_table_tests COMMAND test_hash_table)

add_executable(test_binary_search_tree tests/test_binary_search_tree.c)
target_link_libraries(test_binary_search_tree PRIVATE binary_search_tree)
enable_warnings(test_binary_search_tree)
add_test(NAME binary_search_tree_tests COMMAND test_binary_search_tree)

add_executable(test_memory_pool tests/test_memory_pool.c)
target_link_libraries(test_memory_pool PRIVATE memory_pool)
enable_warnings(test_memory_pool)
add_test(NAME memory_pool_tests COMMAND test_memory_pool)
