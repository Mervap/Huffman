#include "file_reader.h"

file_reader::file_reader(std::string filename) : file_reader(filename, 0) {}

file_reader::file_reader(std::string filename, size_t length) : in(filename, std::ios::binary), leaf_symbols(length) {
    if (in.fail()) {
        in.close();
        throw std::runtime_error("File doesnt exit - \"" + filename + "\"");
    }
}

file_reader::~file_reader() {
    in.close();
}

std::vector<byte> file_reader::read_decoded(size_t cnt) {
    std::vector<byte> result(cnt);
    in.read(reinterpret_cast<char *>(result.data()), cnt);
    result.resize(static_cast<size_t>(in.gcount()));
    return result;
}

encoded_bytes file_reader::read_encoded(size_t count) {
    std::vector<byte> bytes = read_decoded(count);
    encoded_bytes result;
    result.reserve(bytes.size());
    
    for (byte v : bytes) {
        if (leaf_symbols >= 8) {
            result.push_back(v);
        } else {
            result.push_back({static_cast<ull>(v >> (8 - leaf_symbols)), static_cast<byte>(leaf_symbols)});
        }
        leaf_symbols -= 8;
    }

    return result;
}

encoded_bytes file_reader::read_encoded(size_t &size_file, size_t count) {

    std::vector<byte> v(8);
    in.read(reinterpret_cast<char *>(v.data()), 8);
    for (auto c : v) {
        size_file <<= 8;
        size_file |= c;
    }

    v.resize(2);
    in.read(reinterpret_cast<char *>(v.data()), 2);
    for (auto c : v) {
        leaf_symbols <<= 8;
        leaf_symbols |= c;
    }

    return read_encoded(leaf_symbols / 8 + (leaf_symbols % 8 != 0));
}

bool file_reader::eof() {
    return in.eof();
}

void file_reader::set_length(size_t len) {
    leaf_symbols = len;
}
