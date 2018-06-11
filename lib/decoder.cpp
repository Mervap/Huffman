#include "decoder.h"

typedef huffman_tree::node node;


decoder::decoder(encoded_bytes &dict) : tree(huffman_tree(dict)) {}

std::vector<byte> decoder::decode(encoded_bytes &data) {
    std::vector<byte> result;
    if (data.size() == 0) {
        return result;
    }

    size_t i = 0;
    size_t total_size = (data.size() - 1) * 64 + data.get_last();

    node *cur = tree.root;
    while (i < total_size) {
        while (i < total_size && cur != nullptr && !cur->leaf) {
            if (data[i]) {
                cur = cur->r;
            } else {
                cur = cur->l;
            }
            ++i;
        }

        if (cur == nullptr) {
            throw std::runtime_error("File is corrupted");
        }

        if (cur->leaf) {
            result.push_back(cur->symbol);
            cur = tree.root;
        }
    }
    return result;
}