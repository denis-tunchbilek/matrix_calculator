cmake_minimum_required(VERSION 3.20)

project(matrix_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(matrix_core
        src/core/matrix.cpp
        src/core/linalg.cpp
)

target_include_directories(matrix_core PUBLIC src)

add_library(matrix_io
        src/io/matrix_input.cpp
        src/io/matrix_printer.cpp
)

target_include_directories(matrix_io PUBLIC src)
target_link_libraries(matrix_io PUBLIC matrix_core)

add_library(matrix_util
        src/util/value_printer.cpp
)

target_include_directories(matrix_util PUBLIC src)
target_link_libraries(matrix_util PUBLIC matrix_core matrix_io)

add_library(matrix_report
        src/report/info_step.cpp
        src/report/transform_step.cpp
        src/report/property_step.cpp
        src/report/runner.cpp
)

target_include_directories(matrix_report PUBLIC src)
target_link_libraries(matrix_report PUBLIC matrix_core matrix_io matrix_util)

add_executable(matrix_app
        src/app/main.cpp
)

target_include_directories(matrix_app PUBLIC src)
target_link_libraries(matrix_app PRIVATE
        matrix_core
        matrix_io
        matrix_util
        matrix_report
)

add_executable(matrix_tests
        tests/test_input.cpp
        tests/test_print.cpp
        tests/test_linalg.cpp
        tests/test_report.cpp
)

target_include_directories(matrix_tests PUBLIC src)
target_link_libraries(matrix_tests PRIVATE
        matrix_core
        matrix_io
        matrix_util
        matrix_report
        GTest::gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(matrix_tests)