//
// Created by Valery on 10.06.2018.
//

#include <ctime>
#include <iostream>
#include "file_decoder.h"
#include "file_encoder.h"

using namespace std;

void wait_command() {
    cout << "$ ";
    cout.flush();
}

int start() {
    cout << "  Welcome to Huffman encoder!\n  Write \"help\" for commands "
            "list\n";
    wait_command();

    return 0;
}

void help() {
    cout << "Command list:\n";
    cout << "   encode <input file>                - encodes file, output file are <input file>.dec and <input file>.dict\n";
    cout << "   decode <input file> <output file>  - decodes file, find file <input file>.dec and <input file>.dict,\n "
            "                                       result in <output file>\n";
    cout << "   exit                               - exit from encoder\n";
}

vector<string> parse_command(string command) {
    vector<string> result;

    size_t last = 0;
    for (size_t i = 0; i < command.length(); ++i) {
        if (command[i] == ' ') {
            if (i > last) {
                result.push_back(command.substr(last, i - last));
            }

            last = i + 1;
        }
    }
    result.push_back(command.substr(last));
    return result;
}

void encode(vector<string> const &command) {
    try {
        cout << "Encoding...\n";

        clock_t start = clock();

        file_encoder file_encoder(command[1]);
        file_encoder.encode_file();
        file_encoder.write_dictionary();

        clock_t end = clock();
        cout << "Finish. Time spent: " << (double) (end - start) / CLOCKS_PER_SEC * 1000.0 << "ms\n";
    } catch (runtime_error e) {
        cout << "Error occured: \n" << e.what() << "\n";
    }
}

void decode(vector<string> const &command) {
    try {
        cout << "Decoding...\n";

        clock_t start = clock();

        file_decoder file_decoder(command[1]);
        file_decoder.decode_file(command[2]);

        clock_t end = clock();
        cout << "Finish. Time spent: " << (double) (end - start) / CLOCKS_PER_SEC * 1000.0 << "ms\n";
    } catch (runtime_error e) {
        cout << "Error occured: \n" << e.what() << "\n";
    }
}

int main() {
    start();

    string input;
    while (getline(cin, input)) {
        vector<string> command = parse_command(input);
        if (command[0] == "encode") {
            if (command.size() != 2) {
                cout << "Wrong argument amount\n";
            } else {
                encode(command);
            }
        } else if (command[0] == "decode") {
            if (command.size() != 3) {
                cout << "Wrong arguments amount\n";
            } else {
                decode(command);
            }
        } else if (command[0] == "help") {
            help();
        } else if (command[0] == "exit") {
            exit(0);
        } else {
            cout << "No such command\n";
        }
        wait_command();
    }
}