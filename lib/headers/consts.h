//
// Created by Valery on 02.06.2018.
//

#ifndef HUFFMAN_CONSTS_H
#define HUFFMAN_CONSTS_H

#include <array>
#include <exception>
#include <map>
#include <set>
#include <vector>

typedef unsigned char byte;
typedef uint64_t ull;
typedef uint32_t ui;

const size_t MAX_DATA = (1 << 8);
const size_t MAX_SIZE = sizeof(ull) * 8;
const size_t BYTE_SIZE = sizeof(byte) * 8;
const size_t MAX_READ = (1 << 16);

#endif //HUFFMAN_CONSTS_H
