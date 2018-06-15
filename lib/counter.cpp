//
// Created by Valery on 02.06.2018.
//

#include "counter.h"

counter::counter() : cnt(MAX_DATA), times(0) {}

void counter::update(std::vector<byte> const &data) {
    ++times;
    for (auto el : data) {
        ++cnt[el];
    }
}

std::map<byte, ull> counter::get_not_zero() {
    std::map<byte, ull> res;
    for (size_t i = 0; i < MAX_DATA; ++i) {
        if (cnt[i] != 0) {
            res[i] = cnt[i];
        }
    }

    return res;
}

size_t counter::get_times() {
    return times;
}
