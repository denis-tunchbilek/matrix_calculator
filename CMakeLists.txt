cmake_minimum_required(VERSION 3.20)
project(MatrixCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MATRIX_ENABLE_WARNINGS "Enable compiler warnings" ON)

if(MATRIX_ENABLE_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
    elseif(MSVC)
        add_compile_options(/W4)
    endif()
endif()

enable_testing()

add_library(minigtest_main third_party/minigtest/src/gtest_main.cpp)
target_include_directories(minigtest_main PUBLIC third_party/minigtest/include)
add_library(GTest::gtest_main ALIAS minigtest_main)

add_library(matrix_core
        src/core/matrix.cpp
        src/core/linalg.cpp
)
target_include_directories(matrix_core PUBLIC src)
target_compile_features(matrix_core PUBLIC cxx_std_23)

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
target_link_libraries(matrix_app PRIVATE matrix_core matrix_io matrix_util matrix_report)

add_executable(matrix_tests
        tests/test_input.cpp
        tests/test_linalg.cpp
        tests/test_print.cpp
)
target_link_libraries(matrix_tests PRIVATE
        matrix_core
        matrix_io
        matrix_util
        matrix_report
        GTest::gtest_main
)

add_test(NAME matrix_tests COMMAND matrix_tests)