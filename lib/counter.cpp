//
// Created by Valery on 02.06.2018.
//

#include "counter.h"

counter::counter() : cnt(MAX_DATA) {}

void counter::update(std::vector<byte> const &data) {
    for (auto el : data) {
        ++cnt[el];
    }
}

ull counter::get(size_t ind) {
    return cnt[ind];
}

std::map<byte, ull> counter::get_not_zero() {
    std::map<byte, ull> res;
    for (size_t i = 0; i < MAX_DATA; ++i) {
        if (get(i) != 0) {
            res[i] = get(i);
        }
    }

    return res;
}
