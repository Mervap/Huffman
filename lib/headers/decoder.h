//
// Created by Valery on 09.06.2018.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include "consts.h"
#include "counter.h"
#include "huffman_tree.h"
#include "symbol_code.h"
#include "encoded_bytes.h"

struct decoder {
    explicit decoder(encoded_bytes &dict);

    std::vector<byte> decode(encoded_bytes &data);

private:
    huffman_tree tree;
    node* current;
};

#endif //HUFFMAN_DECODER_H