cmake_minimum_required(VERSION 3.14)
project(SimNet)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp src/storage_types.cpp)

add_executable(SimNet ${SOURCE_FILES} main.cpp)

