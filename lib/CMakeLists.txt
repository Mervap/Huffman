project(HUFFMAN_LIBRARY)

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/headers)

set(SOURCES
        counter.cpp
        symbol_code.cpp
        huffman_tree.cpp
        encoder.cpp
        decoder.cpp
        encoded_bytes.cpp)

set(HEADERS
        headers/counter.h
        headers/consts.h
        headers/huffman_tree.h
        headers/symbol_code.h
        headers/encoder.h
        headers/decoder.h
        headers/encoded_bytes.h)

add_library(huffmanLib ${SOURCES} ${HEADERS})
target_include_directories(huffmanLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})