//
// Created by Valery on 02.06.2018.
//
#include "headers/symbol_code.h"

bool symbol_code::empty() {
    return length == 0;
}

void symbol_code::push_back(bool x) {
    code <<= 1;
    code |= x;
    ++length;
}

void symbol_code::pop_back() {
    code >>= 1;
    --length;
}

byte symbol_code::get_length() {
    return length;
}

uint64_t symbol_code::get_code() {
    return code;
}

void symbol_code::clear() {
    length = 0;
    code = 0;
}
