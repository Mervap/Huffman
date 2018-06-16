//
// Created by Valery on 10.06.2018.
//

#ifndef HUFFMAN_FILE_DECODER_H
#define HUFFMAN_FILE_DECODER_H

#include <string>
#include "decoder.h"
#include "file_reader.h"

class file_decoder {
public:
    file_decoder() = delete;
    explicit file_decoder(std::string filename);

    void decode_file(std::string to, std::string mode);

private:
    std::string filename;
    file_reader in;
    encoded_bytes bytes;
    decoder dec;
    size_t file_size;

    ull times;
};

#endif //HUFFMAN_FILE_DECODER_H
