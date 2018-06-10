//
// Created by Valery on 02.06.2018.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include "consts.h"
#include "counter.h"
#include "huffman_tree.h"
#include "symbol_code.h"
#include "encoded_bytes.h"

struct encoder {
    encoder() = delete;
    explicit encoder(counter const &cnt);
    encoded_bytes encode(std::vector<byte> data);

    encoded_bytes dictionary();

private:
    huffman_tree tree;

    void add(encoded_bytes &result, symbol_code &x, bool value);
    void encode_tree(encoded_bytes &result, std::vector<byte> &alf, node *v, symbol_code& x);

};

#endif //HUFFMAN_ENCODER_H
