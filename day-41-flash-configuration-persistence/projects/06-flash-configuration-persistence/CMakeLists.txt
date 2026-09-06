cmake_minimum_required(VERSION 3.16)
project(flash_configuration_persistence C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(NOT MSVC)
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(config_core
    src/config/runtime_config.c
    src/config/crc32.c
    src/config/config_record.c
    src/config/config_store.c)
target_include_directories(config_core PUBLIC include)

add_library(host_flash src/platform/host/host_flash.c)
target_include_directories(host_flash PUBLIC include src/platform/host)
target_link_libraries(host_flash PUBLIC config_core)

add_executable(flash_config_sim src/platform/host/host_main.c)
target_link_libraries(flash_config_sim PRIVATE config_core host_flash)

enable_testing()
add_executable(test_crc_record tests/test_crc_record.c)
target_link_libraries(test_crc_record PRIVATE config_core)
add_test(NAME crc_record_tests COMMAND test_crc_record)

add_executable(test_store tests/test_store.c)
target_link_libraries(test_store PRIVATE config_core host_flash)
add_test(NAME config_store_tests COMMAND test_store)
