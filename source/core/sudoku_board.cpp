#include <algorithm>
#include "sudoku_board.h"
#include "board_treatment.h"
#include "print.h"

namespace sdkg {
    //Contrutor padrão
    SBoard::SBoard(){
        // Tabuleiro vazio
        for(int i{0}; i<SIZE; i++)
            for(int j{0}; j<SIZE; j++)
                m_board[i][j] = 0;
    }
    // Adição de valores ao tabuleiro
   void SBoard::add(int x, int y, int value){
        m_board[x][y] = value;

    }
    // Validação de tabuleiro
    bool SBoard::validate(){
        return is_valid(m_board);
    }
    // Print do tabuleiro
   void SBoard::show_board(){
        print(m_board);
    }
    // Reinicia todas as posições com 0
    void SBoard::clear(){
        for(int i{0}; i<SIZE; i++)
            for(int j{0}; j<SIZE; j++)
                m_board[i][j] = 0;      
    }
}
