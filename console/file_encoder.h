//
// Created by Valery on 10.06.2018.
//

#ifndef HUFFMAN_FILE_ENCODER_H
#define HUFFMAN_FILE_ENCODER_H

#include <string>
#include "file_reader.h"
#include "file_writer.h"
#include "encoded_bytes.h"
#include "encoder.h"

struct file_encoder {
    file_encoder() = delete;

    explicit file_encoder(std::string filename);
    void encode_file(std::string mode);

private:
    std::string filename;
    counter cnt;
    encoder enc;

    size_t file_size;
    counter count_file();
    void write_dictionary(file_writer& out);
};

#endif //HUFFMAN_FILE_ENCODER_H
