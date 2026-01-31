cmake_minimum_required(VERSION 3.10)
project(w3_tests C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Unity test framework
add_library(unity STATIC
    unity/unity.c
    unity/unity.h
    unity/unity_internals.h
)

# Windows-specific libraries
if(WIN32)
    set(WINDOWS_LIBS user32 gdi32)
endif()

# Monitor tests (includes actual monitor.c source)
add_executable(test_monitor
    test_monitor.c
    ../src/monitor.c
)
target_link_libraries(test_monitor unity ${WINDOWS_LIBS})
target_compile_definitions(test_monitor PRIVATE _DEBUG)

# Main utility tests
add_executable(test_main
    test_main.c
)
target_link_libraries(test_main unity ${WINDOWS_LIBS})

# Keyboard tests
add_executable(test_keyboard
    test_keyboard.c
)
target_link_libraries(test_keyboard unity ${WINDOWS_LIBS})

# Shortcuts tests
add_executable(test_shortcuts
    test_shortcuts.c
)
target_link_libraries(test_shortcuts unity ${WINDOWS_LIBS})

# Desktop tests
add_executable(test_desktop
    test_desktop.c
)
target_link_libraries(test_desktop unity ${WINDOWS_LIBS})

# Enable testing
enable_testing()

add_test(NAME test_main COMMAND test_main)
add_test(NAME test_monitor COMMAND test_monitor)
add_test(NAME test_keyboard COMMAND test_keyboard)
add_test(NAME test_shortcuts COMMAND test_shortcuts)
add_test(NAME test_desktop COMMAND test_desktop)

# Add a custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_main test_monitor test_keyboard test_shortcuts test_desktop
    COMMENT "Running all tests..."
)
