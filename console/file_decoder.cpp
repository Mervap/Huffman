//
// Created by Valery on 10.06.2018.
//

#include "file_decoder.h"
#include "file_reader.h"
#include "file_writer.h"
#include "console_color_maker.h"


file_decoder::file_decoder(std::string filename) : filename(filename),
                                                   bytes(file_reader(filename + ".dict").read_encoded(file_size,
                                                                                                      MAX_READ)),
                                                   dec(bytes) {}


void file_decoder::decode_file(std::string to, std::string mode) {
    file_reader in(filename, file_size);
    file_writer out(to);

    if (mode == "testing") {
        while (!in.eof()) {
            encoded_bytes z(in.read_encoded(MAX_READ));
            out.write_decoded(dec.decode(z));
        }
    } else if (mode == "console") {
        size_t i = 1;
        color_maker color;
        color.change_mode();

        while (!in.eof()) {
            encoded_bytes z(in.read_encoded(MAX_READ));
            out.write_decoded(dec.decode(z));

            ull percents = std::min(100ull, 100ull * i /
                                            (file_size > MAX_READ / 8 ? static_cast<ull>(file_size / MAX_READ / 8)
                                                                      : 1));

            if (color.get_mode() == 1 && percents > 33) {
                color.change_mode();
            }
            if (color.get_mode() == 2 && percents > 66) {
                color.change_mode();
            }

            std::cout << "\r" << percents << "%";
            std::cout.flush();
            ++i;
        }
        color.normal_mode();
    }
}