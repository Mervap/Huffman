//
// Created by Valery on 02.06.2018.
//

#include "encoder.h"

typedef huffman_tree::node node;

encoder::encoder(counter const &cnt) : tree(cnt) {}

encoded_bytes encoder::encode(std::vector<byte> data) {
    encoded_bytes result;
    result.reserve(data.size() / 8);
    for (byte i : data) {
        result.push_back(tree.get_code(i));
    }
    return result;
}

encoded_bytes encoder::dictionary() {
    encoded_bytes result;
    std::vector<byte> alf;
    symbol_code x;
    encode_tree(result, alf, tree.root, x);

    for (auto i : alf) {
        result.push_back(i);
    }

    return result;
}

void encoder::add(encoded_bytes &result, symbol_code &x, bool value) {
    x.push_back(value);
    if (x.get_length() == BYTE_SIZE) {
        result.push_back(x);
        x.clear();
    }
}

void encoder::encode_tree(encoded_bytes &result, std::vector<byte> &alf, node *v, symbol_code &x) {
    if (v == nullptr) {
        return;
    }

    if (v->leaf) {
        alf.push_back(v->symbol);
    } else {
        if (v->l != nullptr) {
            add(result, x, 0);
            encode_tree(result, alf, v->l, x);
        }

        if (v->r != nullptr) {
            add(result, x, 0);
            encode_tree(result, alf, v->r, x);
        }
    }

    add(result, x, 1);
    if (v == tree.root && x.get_length() != 0) {
        result.push_back(x);
    }
}


