//
// Created by Valery on 10.06.2018.
//

#include "file_decoder.h"
#include "file_reader.h"
#include "file_writer.h"


file_decoder::file_decoder(std::string filename) : filename(filename),
                                                   bytes(file_reader(filename + ".dict").read_encoded(file_size,
                                                                                                      MAX_READ)),
                                                   dec(bytes) {}


void file_decoder::decode_file(std::string to) {
    file_reader in(filename, file_size);
    file_writer out(to);
    size_t i = 1;
    while (!in.eof()) {
        encoded_bytes z(in.read_encoded(MAX_READ));
        out.write_decoded(dec.decode(z));
        std::cout << "\r" << 100 * i / (file_size / MAX_READ) << "%"; std::cout.flush();
        ++i;
    }
}