cmake_minimum_required(VERSION 3.16)
project(environment_monitor_architecture C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()
add_library(env_core
    src/sensor/sensor_validation.c
    src/service/environment_service.c
    src/app/environment_app.c
)
target_include_directories(env_core PUBLIC include)
add_executable(environment_monitor_sim src/platform/host/host_main.c)
target_link_libraries(environment_monitor_sim PRIVATE env_core)
enable_testing()
add_executable(test_validation tests/test_validation.c)
target_link_libraries(test_validation PRIVATE env_core)
add_test(NAME validation_tests COMMAND test_validation)
add_executable(test_app tests/test_app.c)
target_link_libraries(test_app PRIVATE env_core)
add_test(NAME app_tests COMMAND test_app)
