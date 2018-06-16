cmake_minimum_required(VERSION 3.5)
project(Huffman)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

add_subdirectory(lib)

include_directories("tester/gtest/")

include_directories("console/")

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/headers)

set(CONSOLE_FILES
        console/file_reader.h
        console/file_writer.h
        console/file_encoder.h
        console/file_decoder.h
        console/console_color_maker.h
        console/file_reader.cpp
        console/file_writer.cpp
        console/file_encoder.cpp
        console/file_decoder.cpp
        console/console_color_maker.cpp)

add_executable(Console ${CONSOLE_FILES} console/main.cpp)

add_executable(Huffman_test
        ${CONSOLE_FILES}
        tester/gtest/gtest.h
        tester/gtest/gtest-all.cc
        tester/gtest/gtest_main.cc
        tester/tree_test.cpp)

target_link_libraries(Console huffmanLib -lpthread)
target_link_libraries(Huffman_test huffmanLib -lpthread)