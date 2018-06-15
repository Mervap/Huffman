//
// Created by Valery on 10.06.2018.
//

#include "file_encoder.h"

file_encoder::file_encoder(std::string filename) : filename(filename), cnt(count_file()), enc(cnt) {}

counter file_encoder::count_file() {
    file_reader in(filename);
    counter counter;
    while (!in.eof()) {
        counter.update(in.read_decoded(MAX_READ));
    }
    return counter;
}

void file_encoder::encode_file() {
    file_reader in(filename);
    file_writer out(filename + ".dec");
    size_t i = 1;
    while (!in.eof()) {
        out.write_encoded(enc.encode(in.read_decoded(MAX_READ)));
        std::cout << "\r" << 100 * i / cnt.get_times() << "%"; std::cout.flush();
        ++i;
    }
    file_size = out.get_written_amount();
}

void file_encoder::write_dictionary() {
    file_writer out(filename + ".dec.dict");
    encoded_bytes dict(enc.dictionary());
    encoded_bytes mess;
    mess.push_back({file_size, 64});
    mess.push_back({static_cast<ui>((dict.size() - 1) * 64 + dict.get_last()), 16});
    out.write_encoded(mess);
    out.write_encoded(dict);
}
