#include <iostream>

#include "print.h"
#include "../lib/text_color.h"
#include "sudoku_gm.h"

// Mostra o tabuleiro formatado
void print( short b[SIZE][SIZE] ){
    short cont = 1;
    std::cout <<  Color::tcolor("\n    1 2 3   4 5 6   7 8 9\n", Color::BRIGHT_BLUE, Color::REGULAR);
    for(int i{0}; i<SIZE; i++){
      if(i%3 == 0) std::cout << "  +-------+-------+-------+\n";
      std::cout << Color::tcolor(std::to_string(cont+i) + " ", Color::BRIGHT_BLUE, Color::REGULAR);
      for(int j{0}; j<SIZE; j++){
        if(j%3 == 0) std::cout << "| ";
        if(b[i][j] < 0) std::cout << "  ";
        else std::cout << b[i][j] << " ";
        
      }
      std::cout << "|\n";
      if(i == 8) std::cout << "  +-------+-------+-------+\n";
    } 
}

// Mostra o menu principal
void main_screen(sdkg::SBoard board, std::string msg){
    // Print do título
    std::cout << Color::tcolor("\n\n|--------MAIN SCREEN---------|", Color::BLUE, Color::REGULAR) << std::endl;

    // Print do tabuleiro
    board.show_board();

    // Print das opções de menu
    if(msg.empty()){
      std::cout << Color::tcolor("MSG: []", Color::YELLOW, Color::REGULAR);
    }
    else{
      std::cout << Color::tcolor("MSG: [", Color::YELLOW, Color::REGULAR)
                << Color::tcolor(msg, Color::YELLOW, Color::REVERSE)
                << Color::tcolor("]", Color::YELLOW, Color::REGULAR);
    }
    std::cout << "\n\n1-Play  2-New game  3-Quit  4-Help\n"
              << "Select option [1, 4] > ";
    
}

void action_mode_menu(sdkg::SBoard board){
  // Print do título
  std::cout << Color::tcolor("\n\n|--------ACTION MODE---------|", Color::BLUE, Color::REGULAR) << std::endl;

  // Print do tabuleiro
  board.show_board();

  std::cout << Color::tcolor("Checks left: []\n", Color::YELLOW, Color::REGULAR)
            << Color::tcolor("Digits left: []\n", Color::YELLOW, Color::REGULAR)
            << Color::tcolor("MSG: []\n", Color::YELLOW, Color::REGULAR)
            << Color::tcolor("\nCommands syntax:\n", Color::GREEN, Color::REGULAR)
            << Color::tcolor( "  'enter'(without typing anything) -> go back to the previous menu.\n", Color::GREEN, Color::REGULAR)
            << Color::tcolor( "  'p' <row> <col> <number> + 'enter' -> place <number> on board at location (<row>, <col>).\n", Color::GREEN, Color::REGULAR)
            << Color::tcolor("  'r' <row> <col> + 'enter' -> remove number on board at location (<row>, <col>).\n", Color::GREEN, Color::REGULAR)
            << Color::tcolor("  'c' + 'enter' -> check which moves made are correct.\n", Color::GREEN, Color::REGULAR)
            << Color::tcolor( "  'u' + 'enter' -> undo last play\n", Color::GREEN, Color::REGULAR)
            << Color::tcolor( "  <row>, <col>, <number> must be in range[1, 9].\n\n", Color::GREEN, Color::REGULAR)
            << Color::tcolor("Enter command > ", Color::YELLOW, Color::REGULAR);
}


// Mostra as regras do jogo
void help_sudoku_rules(){
    std::cout << Color::tcolor("\n\n-------------------------------------------------------------------------------------------\n", Color::GREEN, Color::REGULAR)
              << Color::tcolor(" The goal of SUdoku is to fill a 9x9 grid with numbers so that each row, column and 3x3\n section (nonet) contain all of the digits between 1 and 9.\n\n", Color::GREEN, Color::REGULAR)
              << Color::tcolor(" The Sudoku rules are:\n", Color::GREEN, Color::REGULAR )
              << Color::tcolor(" 1. Each row, column, and nonet can contain each number (typically 1 to 9) exactly once.\n", Color::GREEN, Color::REGULAR )
              << Color::tcolor(" 2. The sum of all numbers in any nonet, row, or column must be equal to 45.\n", Color::GREEN, Color::REGULAR )
              << Color::tcolor("-------------------------------------------------------------------------------------------\n\n", Color::GREEN, Color::REGULAR)
              << Color::tcolor("Press enter to go back.", Color::GREEN, Color::REGULAR);
    std::string line;
    std::getline(std::cin, line); 
}