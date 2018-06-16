//
// Created by Valery on 02.06.2018.
//

#ifndef HUFFMAN_ENCODED_BYTES_H
#define HUFFMAN_ENCODED_BYTES_H

#include "consts.h"
#include "counter.h"
#include "symbol_code.h"

struct encoded_bytes {

    encoded_bytes();

    bool empty();
    size_t size();

    void push_back(symbol_code x);
    void push_back(byte x);
    void push_back(ull x);

    byte get_last();
    bool operator[](size_t ind);
    ull const& get(size_t ind);

    void copy(encoded_bytes &other);

    void reserve(size_t n);
    void clear();

private:
    std::vector<ull> value;
    byte prev_size;
};

#endif //HUFFMAN_ENCODED_BYTES_H
