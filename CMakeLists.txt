cmake_minimum_required(VERSION 3.20)

project(MatrixCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix_core
        src/core/matrix.cpp
)

target_include_directories(matrix_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(matrix_io
        src/io/matrix_input.cpp
        src/io/matrix_printer.cpp
)

target_include_directories(matrix_io
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(matrix_io
        PUBLIC
        matrix_core
)

add_library(matrix_util
        src/util/value_printer.cpp
)

target_include_directories(matrix_util
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(matrix_util
        PUBLIC
        matrix_core
        matrix_io
)

add_executable(matrix_app
        src/app/main.cpp
        src/util/value_printer.cpp
)

target_include_directories(matrix_app
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(matrix_app
        PRIVATE
        matrix_core
        matrix_io
        matrix_util
)

enable_testing()