//
// Created by Valery on 10.06.2018.
//

#include <ctime>
#include <iostream>
#include "file_decoder.h"
#include "file_encoder.h"

using namespace std;

int start() {
    cout << "  Welcome to Huffman encoder!\n  Write \"help\" for commands "
            "list\n";
    return 0;
}

void help() {
    cout << "Command list:\n";
    cout
            << "   encode <input file>                - encodes file, output file are <input file>.dec and <input file>.dict\n";
    cout << "   decode <input file> <output file>  - decodes file, find file <input file>.dec and <input file>.dict,\n "
            "                                       result in <output file>\n";
    cout << "   exit                               - exit from encoder\n";
}

void encode(char *command[]) {
    try {
        cout << "Encoding...\n";

        clock_t start = clock();

        std::string s(command[2]);
        file_encoder file_encoder(s);
        file_encoder.encode_file();
        file_encoder.write_dictionary();

        clock_t end = clock();
        cout << "Finish. Time spent: " << (double) (end - start) / CLOCKS_PER_SEC * 1000.0 << "ms\n";
    } catch (runtime_error e) {
        cout << "Error occured: \n" << e.what() << "\n";
    }
}

void decode(char *command[]) {
    try {
        cout << "Decoding...\n";

        clock_t start = clock();

        std::string s1(command[2]);
        std::string s2(command[3]);
        file_decoder file_decoder(s1);
        file_decoder.decode_file(s2);

        clock_t end = clock();
        cout << "Finish. Time spent: " << (double) (end - start) / CLOCKS_PER_SEC * 1000.0 << "ms\n";
    } catch (runtime_error e) {
        cout << "Error occured: \n" << e.what() << "\n";
    }
}

int main(int argc, char *argv[]) {

    if (argc == 1) {
        start();
    } else if (string(argv[1]) == "help") {
        help();
    } else if (string(argv[1]) == "encode") {
        if (argc != 3) {
            cout << "Wrong argument amount\n";
        } else {
            encode(argv);
        }
    } else if (string(argv[1]) == "decode") {
        if (argc != 4) {
            cout << "Wrong argument amount\n";
        } else {
            decode(argv);
        }
    } else {
        cout << "No such command\n";
    }
}
