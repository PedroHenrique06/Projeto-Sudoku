#include <iostream>

#include "print.h"
#include "../lib/text_color.h"
#include "sudoku_gm.h"

// Mostra o tabuleiro formatado
void print( short b[SIZE][SIZE] ){
    short cont = 1;
    // Indices das colunas
    std::cout <<  Color::tcolor("\n    1 2 3   4 5 6   7 8 9\n", Color::BRIGHT_BLUE, Color::REGULAR);
    for(int i{0}; i<SIZE; i++){
      if(i%3 == 0) std::cout << "  +-------+-------+-------+\n";
      // Indices das linhas
      std::cout << Color::tcolor(std::to_string(cont+i) + " ", Color::BRIGHT_BLUE, Color::REGULAR);
      for(int j{0}; j<SIZE; j++){
        if(j%3 == 0) std::cout << "| ";
        // Case: não há número ainda
        if(b[i][j] < 0) std::cout << "  ";
        // Case: prefixo CORRECT
        else if(b[i][j] > 10 && b[i][j] < 20) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_CORRECT), Color::BRIGHT_CYAN, Color::REGULAR) << " ";
        // Case: prefixo INCORRECT
        else if (b[i][j] > 20 && b[i][j] < 30) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_INCORRECT), Color::BRIGHT_CYAN, Color::REGULAR) << " ";
        // Case: prefixo INVALID
        else if (b[i][j] > 30 && b[i][j] < 40) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_INVALID), Color::RED, Color::REGULAR) << " ";
        // Case: ORIGINAL
        else std::cout << b[i][j] << " ";
      }
      std::cout << "|\n";
      if(i == 8) std::cout << "  +-------+-------+-------+\n";
    } 
}

// Faz o print da seta na coluna
void col_arrow(int r){
  std::string pos_arrow = "\n                           ";
  if(r == 1){
    pos_arrow[7] = 'v';
  }
  if(r == 2){
    pos_arrow[9] = 'v';
  }
  else if(r == 3){
    pos_arrow[11] = 'v';
  }
  else if(r == 4){
    pos_arrow[15] = 'v';
  }
  else if(r == 5){
    pos_arrow[17] = 'v';
  }
  else if(r == 6){
    pos_arrow[19] = 'v';
  }
  else if(r == 7){
    pos_arrow[23] = 'v';
  }
  else if(r == 8){
    pos_arrow[25] = 'v';
  }
  else if(r == 9){
    pos_arrow[27] = 'v';
  }
  std::cout << Color::tcolor(pos_arrow, Color::BRIGHT_RED, Color::REGULAR) << std::endl;
}


// Mostra o tabuleiro formatado
void print_with_arrows( short b[SIZE][SIZE], int row, int col){
    short count = 1;
    // Indices das colunas
    col_arrow(col);
    std::cout <<  Color::tcolor("      1 2 3   4 5 6   7 8 9\n", Color::BRIGHT_BLUE, Color::REGULAR);
    for(int i{0}; i<SIZE; i++){
      if(i%3 == 0) std::cout << "    +-------+-------+-------+\n";
      // Indices das linhas
      if((count+i) == row){
        std::cout << Color::tcolor("> ", Color::BRIGHT_RED, Color::REGULAR)<< Color::tcolor(std::to_string(count+i) + " ", Color::BRIGHT_BLUE, Color::REGULAR);
      }
      else{
        std::cout << Color::tcolor("  "+ std::to_string(count+i) + " ", Color::BRIGHT_BLUE, Color::REGULAR);
      }
      for(int j{0}; j<SIZE; j++){
        if(j%3 == 0) std::cout << "| ";
        // Case: não há número ainda
        if(b[i][j] < 0) std::cout << "  ";
        // Case: prefixo CORRECT
        else if(b[i][j] > 10 && b[i][j] < 20) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_CORRECT), Color::BRIGHT_CYAN, Color::REGULAR) << " ";
        // Case: prefixo INCORRECT
        else if (b[i][j] > 20 && b[i][j] < 30) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_INCORRECT), Color::BRIGHT_CYAN, Color::REGULAR) << " ";
        // Case: prefixo INVALID
        else if (b[i][j] > 30 && b[i][j] < 40) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_INVALID), Color::RED, Color::REGULAR) << " ";
        // Case: ORIGINAL
        else std::cout << b[i][j] << " ";
      }
      std::cout << "|\n";
      if(i == 8) std::cout << "    +-------+-------+-------+\n";
    } 
}


// Menu formatado para a checagem
void print_checking( short b[SIZE][SIZE] ){
    short cont = 1;
    // Indices das colunas
    std::cout <<  Color::tcolor("\n    1 2 3   4 5 6   7 8 9\n", Color::BRIGHT_BLUE, Color::REGULAR);
    for(int i{0}; i<SIZE; i++){
      if(i%3 == 0) std::cout << "  +-------+-------+-------+\n";
      // Indices das linhas
      std::cout << Color::tcolor(std::to_string(cont+i) + " ", Color::BRIGHT_BLUE, Color::REGULAR);
      for(int j{0}; j<SIZE; j++){
        if(j%3 == 0) std::cout << "| ";
        // Case: não há número ainda
        if(b[i][j] < 0) std::cout << "  ";
        // Case: prefixo CORRECT
        else if(b[i][j] > 10 && b[i][j] < 20) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_CORRECT), Color::GREEN, Color::REGULAR) << " ";
        // Case: prefixo INCORRECT
        else if (b[i][j] > 20 && b[i][j] < 30) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_INCORRECT), Color::RED, Color::REGULAR) << " ";
        // Case: prefixo INVALID
        else if (b[i][j] > 30 && b[i][j] < 40) std::cout << Color::tcolor(std::to_string(b[i][j] % sdkg::PlayerBoard::prefix_e::PRE_INVALID), Color::RED, Color::REGULAR) << " ";
        // Case: ORIGINAL
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

  // Menu do PLAYING_MODE
void action_mode_menu(sdkg::SBoard board, std::string msg, short checks, int row, int col){
    // Print do título
    std::cout << Color::tcolor("\n\n |--------ACTION MODE---------|", Color::BLUE, Color::REGULAR) << std::endl;

    // Print do tabuleiro
    board.show_board(row, col);

    std::cout << Color::tcolor("  Checks left: [ "+std::to_string(checks)+" ]\n", Color::YELLOW, Color::REGULAR)
              << Color::tcolor("  MSG: [", Color::YELLOW, Color::REGULAR)
              << Color::tcolor( msg, Color::YELLOW, Color::REVERSE)
              << Color::tcolor("]\n", Color::YELLOW, Color::REGULAR)
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
}

// Mostra o menu do QUITTING_MODE
void menu_quitting(sdkg::SBoard board, std::string msg){
    // Print do título
    std::cout << Color::tcolor("\n\n|--------MAIN SCREEN---------|", Color::BLUE, Color::REGULAR) << std::endl;

    // Print do tabuleiro
    board.show_board();

    // mensagem de saída
    std::cout << Color::tcolor("MSG: [", Color::YELLOW, Color::REGULAR)
              << Color::tcolor(msg, Color::YELLOW, Color::REVERSE)
              << Color::tcolor("]", Color::YELLOW, Color::REGULAR)
              << "\n\nYour choise [y/n] > ";
}

// Mostra o menu do REQUESTING_NEW_GAME
void menu_requesting_new_game(sdkg::SBoard board, std::string msg){
    // Print do título
    std::cout << Color::tcolor("\n\n|--------MAIN SCREEN---------|", Color::BLUE, Color::REGULAR) << std::endl;

    // Print do tabuleiro
    board.show_board();

    // mensagem de saída
    std::cout << Color::tcolor("MSG: [", Color::YELLOW, Color::REGULAR)
              << Color::tcolor(msg, Color::YELLOW, Color::REVERSE)
              << Color::tcolor("]", Color::YELLOW, Color::REGULAR)
              << "\n\nYour choise [y/n] > ";
}
// Mostra o menu do CHECKING_MOVES
void menu_cheking(sdkg::SBoard board, std::string msg){
    // Print do título
    std::cout << Color::tcolor("\n\n|--------ACTION MODE---------|", Color::BLUE, Color::REGULAR) << std::endl;

  // Print do tabuleiro formatado com cores
  board.show_board_checking();

  // mensagem de saída
  std::cout << Color::tcolor("MSG: [", Color::YELLOW, Color::REGULAR)
            << Color::tcolor(msg, Color::YELLOW, Color::REVERSE)
            << Color::tcolor("]", Color::YELLOW, Color::REGULAR);

  // Mantém a tela pausada até que o usuário precione enter
  std::string line;
  std::getline(std::cin, line);
}

void menu_finishing(sdkg::SBoard board, std::string msg){
  // Print do título
  std::cout << Color::tcolor("\n\n|--------ACTION MODE---------|", Color::BLUE, Color::REGULAR) << std::endl;

  // Print do tabuleiro
  board.show_board();

  // mensagem de saída
  std::cout << Color::tcolor("MSG: [", Color::YELLOW, Color::REGULAR)
            << Color::tcolor(msg, Color::YELLOW, Color::REVERSE)
            << Color::tcolor("]", Color::YELLOW, Color::REGULAR)
            << "\n\nYour choise [y/n] > ";
}

// Print do menu do jogo finalizado
void menu_finished(sdkg::SBoard board, std::string msg){
  // Print do título
  std::cout << Color::tcolor("\n\n|--------ACTION MODE---------|", Color::BLUE, Color::REGULAR) << std::endl;

  // Print do tabuleiro
  board.show_board_checking();

  // mensagem de saída
  std::cout << Color::tcolor("MSG: [", Color::YELLOW, Color::REGULAR)
            << Color::tcolor(msg, Color::YELLOW, Color::REVERSE)
            << Color::tcolor("]\n", Color::YELLOW, Color::REGULAR);
  
  // Mantém a tela pausada até que o usuário precione enter
  std::string line;
  std::getline(std::cin, line);
}