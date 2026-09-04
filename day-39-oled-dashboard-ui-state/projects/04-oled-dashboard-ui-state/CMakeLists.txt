cmake_minimum_required(VERSION 3.16)
project(oled_dashboard_ui_state C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(ui_core
    src/ui/ui_model.c
    src/ui/ui_renderer.c
)
target_include_directories(ui_core PUBLIC include)

add_executable(oled_dashboard_sim
    src/platform/host/host_main.c
)
target_link_libraries(oled_dashboard_sim PRIVATE ui_core)

enable_testing()

add_executable(test_ui_state tests/test_ui_state.c)
target_link_libraries(test_ui_state PRIVATE ui_core)
add_test(NAME ui_state_tests COMMAND test_ui_state)

add_executable(test_ui_renderer tests/test_ui_renderer.c)
target_link_libraries(test_ui_renderer PRIVATE ui_core)
add_test(NAME ui_renderer_tests COMMAND test_ui_renderer)
