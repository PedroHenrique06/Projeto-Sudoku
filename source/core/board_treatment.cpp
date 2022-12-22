#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "sudoku_board.h" 
#include "sudoku_gm.h"
#include "board_treatment.h"

namespace sdkg{

  // Preenche o vetor de tabuleiros válidos
  void fill_data_base_puzzles(SudokuGame& game){
    coms::Message("Opening input file[" + game.m_opt.input_filename + "].");
    std::fstream file(game.m_opt.input_filename, std::ios::in);
    short number;
    SBoard current_board;
    
    if(not file.is_open()){
      // Mensagem de erro
      ERROR("Error opening file");
    }
    else{
      coms::Message("Processing data, please wait.");
      int row{0};
      int col{0};
      // Laço responsável pela leitura do arquivo
      while(file >> number){
        if(col < SIZE_BOARD){
          current_board.add(row, col, number);                
          col++;
          // Caso a linha esteja totalmente preenchida salta para a próxima
          if(col == SIZE){
            row++;
            col = 0;
          }
          // Caso todas linhas estejam preenchidas valida e adiciona(ou não) ao vetor
          if(row == SIZE){
            if(current_board.validate()){
              game.available_puzzles.push_back(current_board);
            }
            current_board.clear();
            row = 0;
            col = 0;
            }
          }
        }
      }
      file.close();
      coms::Message("Finished reading input data file.");
  }

}

// Valida o tabuleiro
bool is_valid( short b[SIZE][SIZE] ){
    bool numbers[SIZE];
    std::fill(numbers, numbers+SIZE, false);

    // Testando cada linha.
    for(short row{0}; row<SIZE; ++row){
        // "Cadastrar" cada elemento como presente na linha
         for (short col{0}; col<SIZE; ++col){
            auto n=std::abs(b[row][col]);
            // Checa se temos um número fora do intervalo válido
            if(n<1 or n>9) return false;
            numbers[n-1] = true; 
        }
        // Testar se todos os algorismos foram encontrados
        if( not std::all_of(numbers, numbers+SIZE, 
                [](bool e){return e==true;} ) ){
            return false;
        }
        // "Ressetar" o hash de booleanos.
        std::fill(numbers, numbers+SIZE, false);
      }
    // Testando cada coluna.
    for(short row{0}; row<SIZE; ++row){
        // "Cadastrar" cada elemento como presente na linha
        for (short col{0}; col<SIZE; ++col){
            auto n=std::abs(b[col][row]);
        // Checa se temos um número fora do intervalo válido
            if(n<1 or n>9) return false;
            numbers[n-1] = true;
        }
        // Testar se todos os algorismos foram encontrados
        if( not std::all_of(numbers, numbers+SIZE, 
                [](bool e){return e==true;} ) ){
            return false;
        }
        // "Ressetar" o hash de booleanos.
        std::fill(numbers, numbers+SIZE, false);
      }

  // Teste de quadrantes
  // off_sets para calcular o deslocamento dentro dos quadrantes
  int initial_off_set_lines = 0;
  int initial_off_set_columns = 0;
  int off_set_lines = 0; 
  int off_set_columns = 2;
  // Laço que percorrerá cada um dos quadrantes
  for(int num_of_iteration{0}; num_of_iteration<SIZE; num_of_iteration++){
    // Laço que percorrerá o quandrante internamente
    for(int row{initial_off_set_lines}, col{initial_off_set_columns}, i{0}; i<SIZE; i++, col++){
      auto n=std::abs(b[row][col]); 
      // Testa se o número está dentro do intervalo de valores válidos
      if(n<1 or n>9) return false;
      numbers[n-1] = true;   
      //Caso esteja na terceira iteração pula p/ a próxima linha e reinicia a coluna 
      if(col==off_set_columns){
        row++; 
        col = initial_off_set_columns-1;// O -1 foi necessário devido ao col++ do for
      }
    }
    // Testar se todos os algorismos foram encontrados
    if( not std::all_of(numbers, numbers+SIZE, 
                [](bool e){return e==true;} ) ){
        return false;
    } 
    // "Ressetar" o hash de booleanos.
    std::fill(numbers, numbers+SIZE, false);
    
    // Muda quadrante verticalmente
    if(num_of_iteration == 2 || num_of_iteration == 5){
      off_set_lines += 3;
      initial_off_set_lines = off_set_lines;
      initial_off_set_columns = 0;
      off_set_columns = 2;
    }
    else{
      // Muda quadrande horizontalmente
      initial_off_set_lines = off_set_lines;
      initial_off_set_columns += 3;
      off_set_columns += 3;
    }
  }
  return true;
}

