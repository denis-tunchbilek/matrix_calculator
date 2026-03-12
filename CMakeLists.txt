cmake_minimum_required(VERSION 3.20)

project(MatrixCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix_io
        src/io/matrix_input.cpp
        src/io/matrix_input.h
        src/io/matrix_input.cpp
)

target_include_directories(matrix_io
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

enable_testing()