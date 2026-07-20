cmake_minimum_required(VERSION 3.16)
project(smart_environment_monitor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(environment_monitor_core
    src/app/alarm_manager.c
    src/app/environment_monitor.c
    src/app/telemetry.c
)

target_include_directories(environment_monitor_core
    PUBLIC
        include
        src/app
)

add_executable(environment_monitor_sim
    src/platform/host/main.c
    src/platform/host/platform_host.c
)

target_include_directories(environment_monitor_sim
    PRIVATE
        src/platform/host
)

target_link_libraries(environment_monitor_sim
    PRIVATE
        environment_monitor_core
)

enable_testing()

add_executable(test_alarm_manager
    tests/test_alarm_manager.c
)

target_link_libraries(test_alarm_manager
    PRIVATE
        environment_monitor_core
)

add_test(
    NAME alarm_manager_tests
    COMMAND test_alarm_manager
)
