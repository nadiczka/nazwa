cmake_minimum_required(VERSION 3.14)
project(SimNet)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp src/storage_types.cpp src/nodes.cpp src/helpers.cpp src/factory.cpp src/simulation.cpp)

add_executable(SimNet ${SOURCE_FILES} main.cpp)

add_executable(SimNet_debug ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        test/googletest.cpp
        test/test_Factory.cpp
        #test/test_factory_io.cpp #to podobno jest do raportowania
        #test/test_nodes.cpp  #to podobno jest zepsute, bo jak sie dodalo get_receiver_type do IpackageReceiver to nie dziala, a bez tego dzialalo
        test/test_package.cpp
        test/test_simulate.cpp
        test/test_storage_types.cpp
        )

set(HEADER_FILES
        include/config.hpp
        include/helpers.hpp
        include/nodes.hpp
        include/package.hpp
        include/storage_types.hpp
        include/global_functions_mock.hpp
        include/nodes+mocks.hpp
        include/factory.hpp
        include/simulation.hpp
        )

add_executable(SimNet_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(SimNet PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

add_subdirectory(googletest-master)

target_link_libraries(SimNet_test gmock)
