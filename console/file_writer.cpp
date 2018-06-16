//
// Created by Valery on 10.06.2018.
//

#include "file_writer.h"


file_writer::file_writer(std::string filename) : filename(filename),
                                                 out(this->filename, std::ios::binary), was_out(0),
                                                 storage() {}

void file_writer::write_encoded(encoded_bytes data) {
    if (data.empty()) {
        return;
    }

    for (size_t i = 0; i < data.size() - 1; ++i) {
        storage.push_back(data.get(i));
    }

    storage.push_back({(data.get(data.size() - 1) >> (64 - data.get_last())), data.get_last()});

    std::string result;
    result.reserve((storage.size() - 1) * 8);

    for (size_t i = 0; i < storage.size() - 1; ++i) {
        ull x = storage.get(i);
        for (size_t j = 8; j < 65; j += 8) {
            result.push_back(static_cast<byte>((x >> (64 - j)) & 255ull));
        }
    }

    if (storage.get_last() != 0) {
        ull x = storage.get(storage.size() - 1);

        size_t i;
        for (i = 8; i < storage.get_last(); i += 8) {
            result.push_back(static_cast<byte>((x >> (64 - i)) & 255ull));
        }

        if (i == storage.get_last()) {
            result.push_back(static_cast<byte>((x >> (64 - i)) & 255ull));
            storage.clear();
        } else if (i > storage.get_last()) {
            encoded_bytes new_storage;
            new_storage.push_back({((x >> (64 - i + 8 - storage.get_last() % 8)) & 255ull),
                                   static_cast<byte>(storage.get_last() % 8)});
            storage = new_storage;
        }
    } else {
        storage.clear();
    }

    was_out += result.size() * 8;
    out << result;
}

void file_writer::write_decoded(std::vector<byte> data) {
    std::string result;
    result.reserve(data.size());
    for (byte x : data) {
        result.push_back(x);
    }
    out << result;
}


size_t file_writer::get_written_amount() {
    return was_out + (storage.empty() ? 0 : storage.get_last());
}

file_writer::~file_writer() {
    if (!storage.empty()) {
        out << static_cast<byte>((storage.get(0) >> (64 - 8)) & 255);
    }
    out.close();
}

void file_writer::write_remain() {
    if (!storage.empty()) {
        out << static_cast<byte>((storage.get(0) >> (64 - 8)) & 255);
        storage.clear();
        was_out += 8;
    }
}

void file_writer::out_file_size(ull x) {
    ull pos = out.tellp();
    out.seekp(0);

    std::string res;
    for (size_t j = 8; j < 65; j += 8) {
        res.push_back(static_cast<byte>((x >> (64 - j)) & 255ull));
    }

    out << res;
    out.seekp(pos);
}
