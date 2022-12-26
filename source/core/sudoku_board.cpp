#include <algorithm>
#include "sudoku_board.h"
#include "board_treatment.h"
#include "print.h"

namespace sdkg {
    // Contrutor padrão.
    SBoard::SBoard(){
        // Tabuleiro vazio
        for(int i{0}; i<SIZE; i++)
            for(int j{0}; j<SIZE; j++)
                m_board[i][j] = 0;
    }

    // Operador de atribuição.
    SBoard & SBoard::operator=( SBoard &b){
        for (int row = 0; row < SIZE; row++){
            for (int col = 0; col < SIZE; col++){
                this->add(row, col, b.get_element_board(row, col));
            }
        }
        return *this;
    }

   // Adição de valores ao tabuleiro.
   void SBoard::add(int x, int y, short value){
        m_board[x][y] = value;

    }
    // Validação de tabuleiro.
    bool SBoard::validate(){
        return is_valid(m_board);
    }
    // Print do tabuleiro.
   void SBoard::show_board(){
        print(m_board);
    }
    // Print do tabuleiro com setas.
    void SBoard::show_board(int r, int c){
        print_with_arrows(m_board, r, c );
    }

    // Print do tabuleiro com cores.
    void SBoard::show_board_checking(){
        print_checking(m_board);
    }

    // Reinicia todas as posições com 0.
    void SBoard::clear(){
        for(int i{0}; i<SIZE; i++)
            for(int j{0}; j<SIZE; j++)
                m_board[i][j] = 0;      
    }

    // Retorna o valor do tabuleiro na coordenada (x, y).
    short SBoard::get_element_board(int x, int y){
        return m_board[x][y];
    }
    // Altera valor do tabuleiro na coordenada (x, y).
    void SBoard::set_element_board(int x, int y, short valor){
        m_board[x][y] = valor;
    }

    // Construtor passando um Sboard como argumento.
    PlayerBoard::PlayerBoard(SBoard &sb){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                m_solution.add(i, j, sb.get_element_board(i, j));
                m_player_moves.add(i, j, sb.get_element_board(i, j));
            }
        }
    }
    // Checar se o valor informado é correto. 
    bool PlayerBoard::check_in_m_solution(int x, int y, short valor){
        return std::abs(m_solution.get_element_board(x, y)) == valor;
    }
    // Checa se o valor informado é incorreto, porém ainda é uma jogada válida. 
    bool PlayerBoard::check_incorrect(int x, int y){ 
        return (m_player_moves.get_element_board(x, y)/10)*10 == prefix_e::PRE_INCORRECT;
    }
    // Checa se o valor informado é incorreto, porém é uma jogada inválida.
    bool PlayerBoard::check_invalid(int x, int y){ 
        return (m_player_moves.get_element_board(x, y)/10)*10 == prefix_e::PRE_INVALID;
    }

    // Checa se o tabuleiro está correto.
    bool PlayerBoard::check_finished_board(){
        bool equal{true};
        for(int row{0}; row<SIZE; row++){
            for(int col{0}; col<SIZE; col++){
                if((m_player_moves.get_element_board(row, col)%10) != std::abs(m_solution.get_element_board(row, col))){
                    equal = false;
                    return equal;
                }
            }
        }
        return equal;
    }

    // Indica se o tabuleiro está totalmente preenchido.
    bool PlayerBoard::full(){
        bool full{true};
        for(int row{0}; row<SIZE; row++){
            for(int col{0}; col<SIZE; col++){
                if(m_player_moves.get_element_board(row, col) < 0){
                    full = false;
                }
            }
        }
        return full;
    }

    // Reseta o tabuleiro para o tabuleiro da rodada anterior.
    void PlayerBoard::reset_to_previous_board(SBoard &sb){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                m_player_moves.add(i, j, sb.get_element_board(i, j));
            }
        }
    }
    // Operador de atribuição.
    PlayerBoard & PlayerBoard::operator=( PlayerBoard &pb){
        for (int row = 0; row < SIZE; row++){
            for (int col = 0; col < SIZE; col++){
                this->m_solution.add(row, col, pb.get_board_solution().get_element_board(row, col));
                this->m_player_moves.add(row, col, pb.get_board_moves().get_element_board(row, col));
            }   
        }
        return *this;
    }

    // Altera valor do tabuleiro de jogo na coordenada informada (x,y).
    void PlayerBoard::set_element_m_player_moves(int x, int y, short valor){
        m_player_moves.add(x, y, valor);
    }

    // Retorna o board para exibição.
    SBoard PlayerBoard::get_board_moves(){
        return m_player_moves;
    }
    // Retorna o board com a solução.
    SBoard PlayerBoard::get_board_solution(){
        return m_solution;
    }
    // Define o quadrante onde serão feitas as verificações para realizar uma jogada.
    int PlayerBoard::define_quadrant(int row, int col){
        int quadrante = 0;
        // Três primeiros quadrantes.
        if((row >= 0 && row <= 2) && (col >= 0 && col <= 2)){
            quadrante = 1;
        }
        else if((row >= 0 && row <= 2) && (col >= 3 && col <= 5)){
            quadrante = 2;
        }
        else if((row >= 0 && row <= 2) && (col >= 6 && col <= 8)){
            quadrante = 3;
        }
        // Três quadrantes do meios.
        else if((row >= 3 && row <= 5) && (col >= 0 && col <= 2)){
            quadrante = 4;
        }
        else if((row >= 3 && row <= 5) && (col >= 3 && col <= 5)){
            quadrante = 5;
        }
        else if((row >= 3 && row <= 5) && (col >= 6 && col <= 8)){
            quadrante = 6;
        }
        // Últimos quadrantes
        else if((row >= 6 && row <= 8) && (col >= 0 && col <= 2)){
            quadrante = 7;
        }
        else if((row >= 6 && row <= 8) && (col >= 3 && col <= 5)){
            quadrante = 8;
        }
        else if((row >= 6 && row <= 8) && (col >= 6 && col <= 8)){
            quadrante = 9;
        }

        return quadrante;
    }

    // Pecorrer o quadrante onde será realizada a jogada.
    bool PlayerBoard::go_through_quadrant(int l_inicial, int l_final, int c_inicial, int c_final, short value){
        bool valid = true;
        for (int rows{l_inicial}; rows<l_final; rows++){
            for (int cols{c_inicial}; cols<c_final; cols++){
                if(value == m_player_moves.get_element_board(rows, cols) 
                || (value+PRE_CORRECT) == m_player_moves.get_element_board(rows, cols)
                || (value+PRE_INCORRECT) == m_player_moves.get_element_board(rows, cols))
                {
                    valid = false;
                }
            }
        }
        return valid;
    }

    // Verifica se a coordenada informada vai apontar para algum elemento ORIGINAL, ou seja, não pode ser alterado.
    bool PlayerBoard::check_original_pos(int row, int col){
        short pre_increment = m_player_moves.get_element_board(row, col) / 10;
        if(pre_increment == this->PRE_ORIGINAL && m_player_moves.get_element_board(row, col) > 0){
            return true;
        }
        else return false;
    }

    // Testa se é uma jogada valida.
    bool PlayerBoard::valid_move(int row, int col, short value){
        // Validando a linha(x) para verificar se a jogada pode ocorrer.
        bool valid = true;
        for (short cols{0}; cols<SIZE; cols++){
            if(value == m_player_moves.get_element_board(row, cols) 
            || (value+PRE_CORRECT) == m_player_moves.get_element_board(row, cols)
            || (value+PRE_INCORRECT) == m_player_moves.get_element_board(row, cols))
            {
                valid = false;
            }

        }
        // Validando a coluna para verificar se a jogada pode ocorrer.
        if(valid){
            for (short rows{0}; rows<SIZE; rows++){
                if(value == m_player_moves.get_element_board(rows, col) 
                || (value+PRE_CORRECT) == m_player_moves.get_element_board(rows, col)
                || (value+PRE_INCORRECT) == m_player_moves.get_element_board(rows, col))
                {
                    valid = false;
                }
            }

        }
        // Validando a quadrante para verificar se a jogada pode ocorrer.
        if(valid){
            switch (define_quadrant(row, col))
            {
            case 1:
                valid = go_through_quadrant(0, 2, 0, 2, value);
                break;
            case 2:
                valid = go_through_quadrant(0, 2, 3, 5, value);
                break;
            case 3:
                valid = go_through_quadrant(0, 2, 6, 8, value);
                break;

            case 4:
                valid = go_through_quadrant(3, 5, 0, 2, value);
                break;
            case 5:
                valid = go_through_quadrant(3, 5, 3, 5, value);
                break;
            case 6:
                valid = go_through_quadrant(3, 5, 6, 8, value);
                break;

            case 7:
                valid = go_through_quadrant(6, 8, 0, 2, value);
                break;
            case 8:
                valid = go_through_quadrant(6, 8, 3, 5, value);
                break;
            case 9:
                valid = go_through_quadrant(6, 8, 6, 8, value);
                break;
            default:
                break;
            }

        }

        return valid;
    }

    // Altera o tabuleiro que está sendo usado.
    void PlayerBoard::change_board( SBoard& b){
        m_player_moves = b;
    }

}
