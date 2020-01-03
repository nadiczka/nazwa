cmake_minimum_required(VERSION 3.14)
project(SimNet)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp src/storage_types.cpp src/nodes.cpp)

add_executable(SimNet ${SOURCE_FILES} main.cpp)

add_executable(SimNet_debug ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        test/googletest.cpp
        )

add_executable(SimNet_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(SimNet PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

add_subdirectory(googletest-master)

target_link_libraries(SimNet_test gmock)
