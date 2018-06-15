//
// Created by Valery on 15.06.2018.
//

#include <iostream>
#include "console_color_maker.h"


color_maker::color_maker() : current_collor(0) {};

void color_maker::change_mode() {
    std::string s = "\x1b[" + std::to_string(current_collor) + "m";
    std::cout << s;
    ++current_collor;
}

void color_maker::normal_mode() {
    std::cout << "\x1b[0m";
}
