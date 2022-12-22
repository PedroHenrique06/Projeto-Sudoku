#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include "sudoku_board.h"

#define SIZE 9

void print(short[SIZE][SIZE]);
void col_arrow(int);
void print_with_arrows(short[SIZE][SIZE], int, int);
void print_checking(short[SIZE][SIZE]);
void main_screen(sdkg::SBoard, std::string);
void action_mode_menu(sdkg::SBoard, std::string, short, int, int);
void help_sudoku_rules();
void menu_quitting(sdkg::SBoard, std::string);
void menu_requesting_new_game(sdkg::SBoard, std::string);
void menu_cheking(sdkg::SBoard, std::string);
void menu_finished(sdkg::SBoard, std::string);

#endif
