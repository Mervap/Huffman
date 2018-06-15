//
// Created by Valery on 02.06.2018.
//

#ifndef HUFFMAN_COUNTER_H
#define HUFFMAN_COUNTER_H

#include "consts.h"

struct counter {

    counter();

    void update(std::vector<byte> const &data);
    std::map<byte, ull> get_not_zero();

    size_t get_times();
private:
    std::vector<ull> cnt;
    size_t times;
};

#endif //HUFFMAN_COUNTER_H
