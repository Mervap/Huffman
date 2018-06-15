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
    return 0;
}

void help() {
    cout << "Use -cl for command line argument or\n"
            "     -u for command shell\n";
    cout << "Command list:\n";
    cout
            << "   encode <input file>                - encode file, output file are <input file>.dec and <input file>.dec.dict\n";
    cout
            << "   decode <input file> <output file>  - decode file <input file> and <input file>.dict, result in <output file>\n";
    cout << "   exit                               - exit from shell\n";
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

void encode(vector<string> const &args) {
    if (args.size() > 1) {
        cout << "Encoding " << args.size() << " files:\n";
    } else {
        cout << "Encoding 1 file\n";
    }

    clock_t start = clock();

    for (size_t i = 0; i < args.size(); ++i) {
        try {
            if (args.size() > 1) {
                cout << (i != 0 ? "\n" : "") << "File " << i + 1 << ": \"" << args[i] << "\"";
            }

            file_encoder file_encoder(args[i]);
            file_encoder.encode_file();
            file_encoder.write_dictionary();

            if (args.size() > 1) {
                cout << "\nDone!\n";
            }
        } catch (runtime_error e) {
            cout << "Error occured: \n" << e.what() << "\n\n";
        }
    }

    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC * 1000.0;
    string ctime = "ms";

    if(time > 100000) {
        time /= 1000;
        ctime = "s";
    }
    cout << "\nFinish. Time spent: " << time << "ctime" << "\n";
}

void decode(vector<string> const &args) {
    if (args.size() > 2) {
        cout << "Decoding " << args.size() / 2 << " files\n";
    } else {
        cout << "Decoding 1 file\n";
    }

    clock_t start = clock();

    for (size_t i = 0; i < args.size(); i += 2) {
        try {
            if (args.size() > 2) {
                cout << "File " << i / 2 + 1 << ": \"" << args[i] << "\"\n";
            }

            file_decoder file_decoder(args[i]);
            file_decoder.decode_file(args[i + 1]);

            if (args.size() > 2) {
                cout << "Done!\n\n";
            }
        } catch (runtime_error e) {
            cout << "Error occured: \n" << e.what() << "\n\n";
        }
    }

    clock_t end = clock();
    cout << "Finish. Time spent: " << (double) (end - start) / CLOCKS_PER_SEC * 1000.0 << "ms\n";
}

int main(int argc, char *argv[]) {
    std::cout << "a" << "\r";
    if (argc == 1) {
        start();
    } else if (string(argv[1]) == "help") {
        help();
    } else if (string(argv[1]) == "-cl") {
        if (string(argv[2]) == "help") {
            help();
        } else {
            vector<string> args;
            for (int i = 3; i < argc; ++i) {
                args.emplace_back(argv[i]);
            }

            if (string(argv[2]) == "encode") {
                if (args.empty()) {
                    cout << "Wrong argument amount\n";
                } else {
                    encode(args);
                }
            } else if (string(argv[2]) == "decode") {
                if (args.empty() || args.size() % 2 == 1) {
                    cout << "Wrong argument amount\n";
                } else {
                    decode(args);
                }
            } else {
                cout << "No such command\n";
            }
        }
    } else if (string(argv[1]) == "-u") {
        wait_command();
        string input;
        while (getline(cin, input)) {
            vector<string> args = parse_command(input);
            string command = args[0];
            args.erase(args.begin());
            if (command == "encode") {
                if (args.empty()) {
                    cout << "Wrong argument amount\n";
                } else {
                    encode(args);
                }
            } else if (command == "decode") {
                if (args.empty() || args.size() % 2 == 1) {
                    cout << "Wrong arguments amount\n";
                } else {
                    decode(args);
                }
            } else if (command == "help") {
                help();
            } else if (command == "exit") {
                exit(0);
            } else {
                cout << "No such command\n";
            }
            wait_command();
        }
    } else {
        cout << "No such command\n";
    }
}
