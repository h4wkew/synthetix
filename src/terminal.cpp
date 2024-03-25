#include "terminal.h"

#include <iostream>

void hide_cursor()
{
    std::cout << "\033[?25l" << std::endl;
}

void show_cursor()
{
    std::cout << "\033[?25h" << std::endl;
}