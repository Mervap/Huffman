#include "decoder.h"

typedef huffman_tree::node node;


decoder::decoder(encoded_bytes &dict) : tree(huffman_tree(dict)), current(tree.root) {}

std::vector<byte> decoder::decode(encoded_bytes &data) {
    std::vector<byte> result;
    if (data.size() == 0) {
        return result;
    }

    size_t i = 0;
    size_t total_size = (data.size() - 1) * 64 + data.get_last();

    while (i < total_size) {
        while (i < total_size && current != nullptr && !current->leaf) {
            if (data[i]) {
                current = current->r;
            } else {
                current = current->l;
            }
            ++i;
        }

        if (current == nullptr) {
            throw std::runtime_error("File is corrupted");
        }

        if (current->leaf) {
            result.push_back(current->symbol);
            current = tree.root;
        }
    }
    return result;
}