//
// Created by Valery on 15.06.2018.
//

#ifndef HUFFMAN_CONSOLE_COLOR_MAKER_H
#define HUFFMAN_CONSOLE_COLOR_MAKER_H

#include <string>

struct color_maker {

    color_maker();

    void change_mode();
    void normal_mode();

private:
    int current_collor;
    const std::string colors[] = {"31", "33", "32"};
};

#endif //HUFFMAN_CONSOLE_COLOR_MAKER_H
