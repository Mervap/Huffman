//
// Created by Valery on 02.06.2018.
//

#ifndef HUFFMAN_COUNTER_H
#define HUFFMAN_COUNTER_H

#include "consts.h"

struct counter {

    counter();

    void update(std::vector<byte> const &data);
    ull get(size_t ind);
    std::map<byte, ull> get_not_zero();

private:
    std::vector<ull> cnt;
};

#endif //HUFFMAN_COUNTER_H
