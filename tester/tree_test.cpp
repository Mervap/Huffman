#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest.h>
#include <fstream>
#include <bitset>

#include "huffman_tree.h"
#include "encoded_bytes.h"
#include "encoder.h"
#include "decoder.h"
#include "file_encoder.h"
#include "file_decoder.h"

std::vector<byte> encode_decode(std::vector<byte> x) {
    counter cnt;
    cnt.update(x);
    encoder en(cnt);
    encoded_bytes v = en.dictionary();
    decoder dec(v);
    encoded_bytes z = en.encode(x);
    return dec.decode(z);
}

TEST(correctness, bamboo) {
    std::vector<byte> x = {1, 1, 1, 1, 3, 3, 3, 0, 0, 2};
    std::vector<byte> y = encode_decode(x);
    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}

TEST(correctness, balance) {
    std::vector<byte> x = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
    std::vector<byte> y = encode_decode(x);

    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}

TEST(correctness, fill) {
    std::vector<byte> x = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<byte> y = encode_decode(x);

    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}

TEST(correctness, random) {
    size_t count = 30;

    for (size_t i = 0; i < count; ++i) {
        std::vector<byte> x(static_cast<size_t>(rand() % 200000));
        for (unsigned char &j : x) {
            j = (static_cast<byte>(rand() % MAX_DATA));
        }

        std::vector<byte> y = encode_decode(x);

        EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));

        /*for(size_t j = 0; j < z.size(); ++j) {
            std::cout << std::bitset<sizeof(z.get(j)) * 8>(z.get(j));
        }
        std::cout << "\n";                                              // Some info
        for (int i = 0; i < x.size(); ++i) {
            std::cout << (int) x[i] << " " << (int) y[i] << "\n";
        }*/
    }
}

TEST(correctness, 10MB) {
    std::vector<byte> x(static_cast<size_t>(10 * 1024 * 1024));
    for (unsigned char &j : x) {
        j = (static_cast<byte>(rand() % MAX_DATA));
    }

    std::vector<byte> y = encode_decode(x);

    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}

TEST(correctness, empty) {

    std::vector<byte> x;
    std::vector<byte> y = encode_decode(x);

    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}

bool file_encode_decode(std::string const &in_name) {
    file_encoder fe(in_name);
    fe.encode_file("testing");

    file_decoder file_decoder(in_name + ".dec");
    file_decoder.decode_file(in_name + "_check", "testing");

    std::ifstream in1(in_name, std::ios::binary);
    std::ifstream in2(in_name + "_check", std::ios::binary);

    std::vector<byte> a1(MAX_READ);
    std::vector<byte> a2(MAX_READ);
    while (!in1.eof()) {
        in1.read(reinterpret_cast<char *>(a1.data()), MAX_READ);
        in2.read(reinterpret_cast<char *>(a2.data()), MAX_READ);

        if (!std::equal(a1.begin(), a1.end(), a2.begin())) {
            in1.close();
            in2.close();
            remove(std::string(in_name + ".dec").c_str());
            remove(std::string(in_name + "_check").c_str());
            return false;
        }
    }

    in1.close();
    in2.close();
    remove(std::string(in_name + ".dec").c_str());
    remove(std::string(in_name + "_check").c_str());
    return true;
}

TEST(correctness, file_symbol) {
    EXPECT_TRUE(file_encode_decode("symbol"));
}

TEST(correctness, file_bamboo) {
    EXPECT_TRUE(file_encode_decode("bamboo"));
}

TEST(correctness, file_balance) {
    EXPECT_TRUE(file_encode_decode("balance"));
}

TEST(correctness, file_fill) {
    EXPECT_TRUE(file_encode_decode("fill"));
}

TEST(correctness, file_1MB) {
    EXPECT_TRUE(file_encode_decode("1MB"));
}

TEST(correctness, file_empty) {
    EXPECT_TRUE(file_encode_decode("empty"));
}