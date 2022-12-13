#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include "sudoku_board.h"

#define SIZE 9

void print(short[SIZE][SIZE]);
void main_screen(sdkg::SBoard, std::string);
void action_mode_menu(sdkg::SBoard);
void help_sudoku_rules();

#endif