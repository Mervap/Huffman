//
// Created by Valery on 02.06.2018.
//

#include <encoded_bytes.h>

encoded_bytes::encoded_bytes() : value(), prev_size(MAX_SIZE) {}

size_t encoded_bytes::get_last() {
    return prev_size;
}

void encoded_bytes::push_back(symbol_code x) {
    if (prev_size == MAX_SIZE) {
        value.push_back(x.get_code() << (MAX_SIZE - x.get_length()));
        prev_size = x.get_length();
    } else {
        if (prev_size + x.get_length() > MAX_SIZE) {
            size_t new_size = (x.get_length() - (MAX_SIZE - prev_size));
            value[value.size() - 1] |= (x.get_code() >> new_size);
            value.push_back(x.get_code() << (MAX_SIZE - new_size));
            prev_size = new_size;
        } else {
            value[value.size() - 1] |= (x.get_code() << (MAX_SIZE - prev_size - x.get_length()));
            prev_size += x.get_length();
        }
    }
}


void encoded_bytes::push_back(byte x) {
    push_back({x, BYTE_SIZE});
}

bool encoded_bytes::empty() {
    return value.empty();
}

size_t encoded_bytes::size() {
    return value.size();
}

bool encoded_bytes::operator[](size_t ind) {
    return static_cast<bool>((value[ind / 64] >> (63 - (ind % 64))) & 1);
}

ull const &encoded_bytes::get(size_t ind) {
    return value[ind];
}

void encoded_bytes::clear() {
    value.clear();
    prev_size = 64;
}

void encoded_bytes::reserve(size_t n) {
    value.reserve(n);
}