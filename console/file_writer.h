//
// Created by Valery on 10.06.2018.
//

#ifndef HUFFMAN_WRITER_H
#define HUFFMAN_WRITER_H

#include <fstream>
#include <string>
#include <vector>
#include "encoded_bytes.h"
#include "consts.h"

struct file_writer {
    file_writer() = delete;

    explicit file_writer(std::string filename);

    void write_encoded(encoded_bytes data);
    void write_decoded(std::vector<byte> data);

    size_t get_written_amount();
    ~file_writer();

private:
    std::string filename;
    std::ofstream out;

    size_t was_out;
    encoded_bytes storage;
};

#endif //HUFFMAN_WRITER_H
