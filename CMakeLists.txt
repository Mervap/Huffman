cmake_minimum_required(VERSION 3.5)
project(Huffman)

set(CMAKE_CXX_STANDARD 11)

include_directories("tester/gtest/")

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/headers)

add_executable(Console
        console/file_reader.h
        console/file_writer.h
        console/file_encoder.h
        console/file_decoder.h
        console/console_color_maker.h
        console/file_reader.cpp
        console/file_writer.cpp
        console/file_encoder.cpp
        console/file_decoder.cpp
        console/console_color_maker.cpp
        console/main.cpp)

add_executable(Huffman_test
        tester/gtest/gtest.h
        tester/gtest/gtest-all.cc
        tester/gtest/gtest_main.cc
        tester/tree_test.cpp)

add_subdirectory(lib)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -std=c++17 -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -pedantic")

target_link_libraries(Console huffmanLib -lpthread)
target_link_libraries(Huffman_test huffmanLib -lpthread)