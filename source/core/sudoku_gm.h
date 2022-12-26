#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

/*!
 *  SUdoku game class header.
 */

#include <fstream>
#include <thread>
#include <memory>
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::fill_n;
using std::all_of;
#include <vector>
using std::vector;
#include <iterator>
using std::back_inserter;
#include <sstream>
using std::ostringstream;
#include <numeric>
using std::accumulate;
#include <stack>

// Definição de nomenclatura.
using uint = unsigned int;

#include "../lib/messages.h"
#include "../lib/text_color.h"
#include "sudoku_board.h"

namespace sdkg {

    /// Game class representing a Life Game simulation manager.
    class SudokuGame{
        private:
            //=== Structs

            //!< Possible game states.
            enum class game_state_e : uint {
                STARTING=0,             //!< Beginning the game.
                //====================================================
                READING_MAIN_OPT,       //!< Reading main menu option.
                //----------------------------------------------------
                HELPING,                //!< Displaying game rules (main menu)
                QUITTING,               //!< Game is quiting either because user requested (main menu).
                //====================================================
                PLAYING_MODE,           //!< Reading user command (Play sub-menu).
                //----------------------------------------------------
                REQUESTING_NEW_GAME,    //!< User wants to start a new game.
                CONFIRMING_QUITTING_MATCH,    //!< User has already started a match. We need to confimr s/he wants to bail out.
                VALIDATING_PLAY,        //!< User wants to place a number on the board.
                REMOVING_PLAY,          //!< User wants to remove a number from the board.
                CHECKING_MOVES,         //!< User wants to check whether his previous moves are correct.
                UNDOING_PLAY,           //!< User wants to undo a previous move he did.
                // ====================================================
                FINISHED_PUZZLE,         //!< User has completed the board. 
            };


            /// Internal game options
            struct Options {
                std::string input_filename; //!< Input cfg file.
                short total_checks;        //!< # of checks user has left.
            };

            /// Options from the main menu.
            enum class main_menu_opt_e : uint {
                PLAY=1,        //!< Play option.
                NEW_GAME,      //!< New puzzle option.
                QUIT,          //!< Quit option.
                HELP,          //!< Print help option.
                WAITING,       //!< Wating for the menu option.
            };

            /// Represents a user move.
            struct Play {
                short row;    //!< row selected by the user.
                short col;    //!< col selected by the user.
                short value;  //!< value to play selected by the user.
                /// Constructor.
                Play( short r=-1, short c=-1, short v=1 ) : row{r}, col{c}, value{v}{/*empty*/}
            };

            /// Represents a command issued during a match (UNDO command).
            struct Command {
                enum class type_e : uint {
                    PLACE=0, //!< Place command.
                    REMOVE   //!< Remove command.
                } action ;
                Play data; //!< Play data.

                Command( type_e a, Play p ) : action{a}, data{p}
                { /* empty */ }
            };


            //=== Data members

            Options m_opt;                          //!< Overall game Options to set up the game configuration.
            game_state_e m_game_state;              //!< Current game state.
            std::string m_curr_msg = "";            //!< Current message to display on screen.
            Play m_curr_play;                       //!< Current user play.
            bool m_game_over;                       //!< Flag that indicates if the game has ended or not.
            bool m_full_board;                      //!< Flag that indicates if the board is complete.
            bool m_quiting_game;                    //!< Flag that indicates if the player is quitting the game.
            short m_checks_left;                    //!< Current # of checks user can request.
            unsigned new_game_board = 0;            //!< Auxiliar variable used to calculates off_set_board.
            unsigned off_set_board = 0;             //!< Indicates the index of the current board to be showed.
            main_menu_opt_e m_curr_main_menu_opt;   //!< Current main menu option.
            std::vector<SBoard> available_puzzles;  //!< List of available puzzles.
            std::stack <SBoard> stack_moves;        //!< Stack containing the board's move history
            PlayerBoard player;                     //!< The current board that's being played


        public:
            SudokuGame();
            ~SudokuGame();

            void initialize(int, char**);
            void display_welcome();
            void usage(std::string)const;
            void set_game();
            void process_events();
            void update();
            bool is_complete();
            void render();
            bool game_over();
             
            friend void fill_data_base_puzzles(SudokuGame&);

    }; // SudokuGame class.
}
#endif
