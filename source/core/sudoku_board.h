#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

/*!
 *  In this header file we have two classes: SBoard and SudokuPlayerBoard.
 *
 *  The former represents only the board data, as a matrix of short.
 *
 *  The latter represents the board and the actions necessary to support
 *  the player's moves and all the information associated with a
 *  Sudoku match. This involves enconding information regarding incorrect
 *  moves, invalid plays, correct play, original numbers, etc.
 *  These information is required to display the board with special colors
 *  representing all thesse different conditions.
 */

#include "board_treatment.h"

#define SIZE 9
#define EMPTY_VALUE -1

namespace sdkg {

    /// This class stores values for a 9x9 Sudoku board.
    class SBoard {
        public:
            SBoard();
            SBoard & operator=( SBoard & );
            void add(int, int, short);
            bool validate();
            void show_board();
            void show_board(int, int);
            void show_board_checking();
            void clear();
            short get_element_board(int x, int y);
            void set_element_board(int x, int y, short valor);
        private:
            short m_board[SIZE][SIZE];
    };


    /*!
     *  This class represents a Sudoku board as the player's makes his or her moves during a match.
     *  The moves in the board data set is coded as follows:
     *
     *  + Digits in range [1,9]: These are the original values already filled in when the match started.
     *  + 0: An empty location that may receive a value provided by the player.
     *  + prefix `1` as in 1[1,9]: We add this prefix if the player's value is correct, i.e. corresponds
     *    to the correct value stored in the solution elsewhere.
     *  + prefix `2` as in 2[1,9]: We add this prefix if the player's value is incorrect, i.e. it is
     *    a valid play but it differs from the solution.
     *  + prefix `3` as in 3[1,9]: We add this prefix if the player makes an invalid move, i.e. a move
     *    that breaks the Sudoku's basic rules.
     *
     *  Note that the player's moves are always stored, when it is applied to a location that does
     *  not contain an original value.
     *  This is important so we can color the number accordingly when we display the board.
     */
    class PlayerBoard {
        private:
            SBoard m_player_moves; //!< The Sudoku matrix where the user moves are stored.
            SBoard m_solution;     //!< The Sudoku matrix with the solution.

        public:
            /// Possible types associated with a location on the board druring a match.
            enum loc_type_e : short {
                EMPTY = 0,      //!< Empty cell.
                ORIGINAL,       //!< Original puzzle value, not mutable.
                CORRECT,        //!< Correct value.
                INCORRECT,      //!< Incorrect value.
                INVALID         //!< Invalid play.
            };

            /// Prefix we may add to a stored value to encode information.
            enum prefix_e : short {
                PRE_ORIGINAL = 0,
                PRE_CORRECT = 10,   //!< User has entered a correct value.
                PRE_INCORRECT = 20, //!< User has entered an incorrect value.
                PRE_INVALID = 30    //!< User has entered an invalid value.
            };

        public:
            //=== Regular methods.
            PlayerBoard(){/*empty*/}
            PlayerBoard(SBoard &sb );
            ~PlayerBoard(){/*empty*/}
            PlayerBoard & operator=( PlayerBoard & );
            PlayerBoard( const PlayerBoard & ) = delete;

            //=== Access methods.
            bool check_in_m_solution(int x, int y, short valor);
            bool check_incorret(int x, int y);
            bool check_invalid(int x, int y);
            short get_element_board(int x, int y);
            SBoard get_board_moves();
            SBoard get_board_solution();
            bool valid_move(int x, int y, short valor);
            bool check_finished_board();
            bool full();
            bool check_original_pos(int row, int col);
            bool pecorrer_quadrante(int row_ini, int row_fin, int col_ini, int col_fin, short value);
            int definir_quadrante(int row, int col);
        
            //=== Modifiers methods.
            void reset_to_previous_board(SBoard &sb);    
            // Altera valor do tabuleiro de jogo na coordenada informada (x,y);
            void set_element_m_player_moves(int x, int y, short valor);
            // Altera o tabuleiro que está sendo usado
            void change_board(SBoard&);

    };
}
#endif
