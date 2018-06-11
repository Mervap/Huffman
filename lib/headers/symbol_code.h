//
// Created by Valery on 02.06.2018.
//

#ifndef HUFFMAN_SYMBOL_CODE_H
#define HUFFMAN_SYMBOL_CODE_H

#include "consts.h"

struct symbol_code {

    symbol_code() : code(0), length(0) {}

    symbol_code(ull x, byte l) : code(x), length(l) {}
    symbol_code(byte x) : code(x), length(8) {}

    void push_back(bool x);
    void pop_back();

    byte get_length();
    ull get_code();

    void clear();

private:
    ull code;
    byte length;
};

#endif //HUFFMAN_SYMBOL_CODE_H
