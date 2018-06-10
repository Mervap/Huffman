#ifndef HUFFMAN_READER_H
#define HUFFMAN_READER_H

#include <fstream>
#include <iostream>
#include <vector>

#include "encoded_bytes.h"
#include "consts.h"

struct file_reader {
    file_reader() = delete;

    explicit file_reader(std::string filename);
    explicit file_reader(std::string filename, size_t length);

    std::vector<byte> read_decoded(size_t cnt);
    encoded_bytes read_encoded(size_t count);
    encoded_bytes read_encoded(size_t &size_file, size_t count);

    ~file_reader();

    bool eof();

private:
    std::ifstream in;
    size_t leaf_symbols;
};

#endif  // HUFFMAN_READER_H