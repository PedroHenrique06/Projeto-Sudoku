#include <cassert>
#include <stdexcept>
#include <iterator>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <bits/stdc++.h>
#include "sudoku_gm.h"
#include "board_treatment.h"
#include "print.h"

// Função para dividir uma string em várias partes.
std::vector<std::string> split(const std::string & input_str, char delimiter=' '){
    // Armazena os tokens 
    std::vector<std::string> tokens;
    // Lê os tokens do buffer de strings
    std::istringstream iss;
    iss.str(input_str);
    // Armazenará um único token temporareamente.
    std::string token;
    while (std::getline(iss >> std::ws, token, delimiter))
        tokens.emplace_back(token);
    return tokens;
}


namespace sdkg {

    // Expressão lambda que transforma uma string em minúscula.
    auto STR_LOWERCASE = [](const char * t)->std::string{
        std::string str{ t };
        std::transform( str.begin(), str.end(), str.begin(), ::tolower );
        return str;
    };

    // Função lambda para testar se o valor é um número.
    auto IS_DIGIT = [](std::string number)->bool{
        if(all_of(number.begin(), number.end(), [](char digit)->bool{ return isdigit(digit); })){
            return true;
        }
        return false;
     };

    // Construtor padrão.
    SudokuGame::SudokuGame(){
        m_opt.total_checks = 3; // Valor padrão.
        m_opt.input_filename = "../data/input.txt"; // Valor padrão.
    }

    // Trata os argumentos passados por linha de comando.
    void SudokuGame::initialize(int argc, char** argv){
        std::vector<std::string> argumentos(argc);

        for(int i{1}; i<argc; i++){
            argumentos[i] = STR_LOWERCASE(argv[i]);
        }
        // Tratamento dos argumentos da linha de comando.
        if(argc == 2 ){
            if(argumentos[1] == "--help" || std::string(argv[1]) == "-h") usage("");
            // Testa se o argumento é [-c], caso seja, acusa falta de complemtento.
            else if(argumentos[1] == "-c") usage(Color::tcolor("Lacking complement of argument", Color::YELLOW, Color::REGULAR));
            else{
                m_opt.input_filename = argumentos[1];
            }
        }
        else if(argc == 3){
            if(argumentos[1] == "-c"){
            // Testa se após [-c] há um número.
                if(IS_DIGIT(argumentos[2])){
                    m_opt.total_checks = std::stoi(argumentos[2]);
                }
                else usage(Color::tcolor("The complement of the -c has to be an integer", Color::YELLOW, Color::REGULAR));
            }
        }
        else if(argc == 4){
            if(argumentos[1] == "-c"){
                // Testa se após [-c] há um número.
                if(IS_DIGIT(argumentos[2])){
                    m_opt.total_checks = std::stoi(argumentos[2]); 
                    m_opt.input_filename = argumentos[3];
                }
                else usage("The complement of the -c has to be an integer");
            }    
        }
    fill_data_base_puzzles(*this);
    m_game_state = SudokuGame::game_state_e::STARTING;
    }

    // Mostra uma mensagem de boas vindas.
    void SudokuGame::display_welcome(){
        std::cout << "\n==================================================================\n" 
                  << "\tWelcome to a terminal version of Sudoku, v1.0\n"
                  << "\tCopyright (C) 2020, Selan R. dos Santos\n"
                  << "==================================================================\n"
                  << "\nPress enter to start.";
        // Mantém a tela pausada até que o usuário precione enter.
        std::string line;
        std::getline(std::cin, line);
    }

    // Mostra o menu de uso do programa.
    void SudokuGame::usage( std::string msg ) const{
        if ( msg != "" ) std::cerr << "sudoku: " << msg << "\n\n";

        std::cerr << "Usage: sudoku [-c <num>] [--help] <input_puzzle_file>\n"
                  << "  Game options:\n"
                  << "    -c     <num> Number of checks per game. Default = 3.\n"
                  << "    --help       Print this help text.\n";
        std::cerr << std::endl;

        exit( msg != "" ? 1 : 0 );
    }
    
    // Prepara o tabuleiro e as checagens.
    void SudokuGame::set_game(){
        m_checks_left = m_opt.total_checks;
        PlayerBoard p(available_puzzles[off_set_board]);
        player = p;
        m_full_board = false;
        m_game_over = false;
        m_quiting_game = false;
    }

    // Testa se o tabuleiro está completo.
    bool SudokuGame::is_complete(){
        if(player.full()){
            m_full_board = true;
        }
        return m_full_board;
    }


    // Processa os eventos e altera os estados.
    void SudokuGame::process_events(){
        if ( m_game_state == game_state_e::STARTING or
             m_game_state == game_state_e::HELPING  or
             m_game_state == game_state_e::CHECKING_MOVES)
        {
            if(m_game_state == game_state_e::STARTING){
                set_game();
                m_game_state = game_state_e::READING_MAIN_OPT;
            }
            else if(m_game_state == game_state_e::CHECKING_MOVES){
                m_game_state = game_state_e::PLAYING_MODE;
            }
            else if (m_game_state == game_state_e::HELPING){
                m_game_state = game_state_e::READING_MAIN_OPT;
            }
        }
        else if ( m_game_state == game_state_e::READING_MAIN_OPT ){
            std::string option; 
            std::string aux;
            // Captura da opção escolhida.
            std::getline(std::cin, aux);
            std::istringstream iss{aux};
            iss >> option;

            // Teste para checar se é um número.
            if(IS_DIGIT(option)){
                m_curr_main_menu_opt = main_menu_opt_e(std::stoi(option));
                // Teste para checar se está no intervalo válido de opções.
                if( std::stoi(option) <= 0 or std::stoi(option) > 4 ){
                    m_curr_msg ="The value is outside of the valid range of options";
                }
            }
            else{
                m_curr_msg = "The entry has to be a number";
            }            
        }
        else if ( m_game_state == game_state_e::PLAYING_MODE ){
            std::string op;
            
            // Captura a linha com o comando.
            std::getline(std::cin, op); 

            std::vector<std::string> line = split(op, ' ');
            
            // Case 'enter' .
            if(line.size() == 0){
                m_game_state = game_state_e::READING_MAIN_OPT;
            }

            // Case 'p'.
            if(line.size() == 4 and (line[0] == "p" or line[0] == "P")){
                // Validação dos valores
                if(not(IS_DIGIT(line[1]) and IS_DIGIT(line[2]) and IS_DIGIT(line[3]))){
                   m_curr_msg = "The entry has to be a number";
                }
                else{
                    m_curr_play.row = short(std::stoi(line[1]));
                    m_curr_play.col = short(std::stoi(line[2]));
                    m_curr_play.value = short(std::stoi(line[3]));
                    Command(Command::type_e::PLACE, m_curr_play); 

                    if(m_curr_play.row < 0 or m_curr_play.row > 9 or m_curr_play.col < 0 or m_curr_play.col > 9){
                        m_curr_msg = "The value of <row> or <col> is outside of the range of valid values";

                    }
                    else if(m_curr_play.value <= 0 or m_curr_play.value > 9){
                        m_curr_msg = "The value of <number> is outside of the range of valid values";
                    }
                    else{
                        m_game_state = game_state_e::VALIDATING_PLAY;
                    }
                }
            }         

            // Case 'r'.
            if(line.size() == 3 and (line[0] == "r" or line[0] == "R")){
                if(not(IS_DIGIT(line[1]) and IS_DIGIT(line[2]))){
                   m_curr_msg = "The entry has to be a number";
                }
                else{
                    m_curr_play.row = short(std::stoi(line[1]));
                    m_curr_play.col = short(std::stoi(line[2]));
                    Command(Command::type_e::REMOVE, m_curr_play);
                    
                    if(m_curr_play.row < 0 or m_curr_play.row > 9 or m_curr_play.col < 0 or m_curr_play.col > 9){
                        m_curr_msg = "The value of <row> or <col> is outside of the range of valid values";
                    }
                    else{
                        m_game_state = game_state_e::REMOVING_PLAY;
                    }
                }
            }

            // Case 'c'.
            if(line.size() == 1 and (line[0] == "c" or line[0] == "C")){
                // Checa se há checks diponíveis.
                if(m_checks_left <= 0){
                    m_curr_msg = "You have no checks left to use";
                }
                else{
                    m_curr_msg = "Checking moves. Press enter to continue";
                    m_game_state = game_state_e::CHECKING_MOVES;
                }
            }

            // Case 'u'.
            if(line.size() == 1 and (line[0] == "u"  or line[0] == "U")){
                m_game_state = game_state_e::UNDOING_PLAY;
            }
        }
        else if( m_game_state == game_state_e::REQUESTING_NEW_GAME){
            char new_game;
            std::string aux;
            // Captura da resposta.
            std::getline(std::cin, aux);

            std::istringstream iss{aux};

            iss >> new_game;

            if(new_game == 'y' or new_game == 'Y'){
                // Muda o tabuleiro que é mostrado no menu principal.
                new_game_board++;
                off_set_board = new_game_board % available_puzzles.size();
                m_checks_left = m_opt.total_checks;
                m_curr_msg = "";
                m_game_state = game_state_e::STARTING;    
            }
            else{
                m_curr_msg = "";
                m_game_state = game_state_e::READING_MAIN_OPT;
            }
        }
        else if ( m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH ){        
            char exit;
            std::string aux;
            // Captura da resposta.
            std::getline(std::cin, aux);

            std::istringstream iss{aux};

            iss >> exit;

            if(exit == 'y' or exit == 'Y'){
                m_game_over = true;
                game_over();
            }
            else{
                m_curr_msg = "";
                m_game_state = game_state_e::READING_MAIN_OPT;
            }
        }
        else if(m_game_state == game_state_e::FINISHED_PUZZLE){
                if(player.check_finished_board()){
                    m_curr_msg = "Congratulations you've completed the puzzle correctly, press enter to continue";
                    m_quiting_game = true;
                }
                else{
                    m_curr_msg = "Sorry, you lost, press enter to continue";
                    m_quiting_game = true;
                }
        } 

    }

    // Atualiza as opções e status do jogo conforme as indicações do usuário.
    void SudokuGame::update(){
        // STATES OF READING_MENU_MODE

        // PLAY
        if(m_curr_main_menu_opt == main_menu_opt_e::PLAY){
                m_game_state = game_state_e::PLAYING_MODE;
                m_curr_main_menu_opt = main_menu_opt_e::WAITING;
            }
        // NEW_GAME
        else if(m_curr_main_menu_opt == main_menu_opt_e::NEW_GAME){
            m_curr_msg = Color::tcolor("Are you sure you want a new game? You will lose the current progress", Color::YELLOW, Color::REVERSE);
            m_game_state = game_state_e::REQUESTING_NEW_GAME;
            m_curr_main_menu_opt = main_menu_opt_e::WAITING;
        }
        // QUIT
        else if(m_curr_main_menu_opt == main_menu_opt_e::QUIT){
            // Testar se há um jogo em curso passar para o QUITTING_MATCH 
            // TODO
            
            m_curr_msg = Color::tcolor("Are you sure you want to leave this game?", Color::YELLOW, Color::REVERSE);
            m_game_state = game_state_e::CONFIRMING_QUITTING_MATCH;
            m_curr_main_menu_opt = main_menu_opt_e::WAITING;
        }
        // HELP
        else if(m_curr_main_menu_opt == main_menu_opt_e::HELP){
            m_game_state = game_state_e::HELPING;
            m_curr_main_menu_opt = main_menu_opt_e::WAITING;
        }

        // STATES OF PLAYING_MODE

        // VALIDATING_PLAY
        if(m_game_state == game_state_e::VALIDATING_PLAY){
                
            if (not player.check_original_pos(m_curr_play.row-1, m_curr_play.col-1))
            {
                // Adiciona a versão na pilha antes que ela seja alterada.
                stack_moves.push(player.get_board_moves());

                if(player.check_in_m_solution(m_curr_play.row-1, m_curr_play.col-1, m_curr_play.value)){
                    
                m_curr_play.value += player.PRE_CORRECT;
                    player.set_element_m_player_moves(m_curr_play.row-1, m_curr_play.col-1, m_curr_play.value);
                }
                else if(player.valid_move(m_curr_play.row-1, m_curr_play.col-1, m_curr_play.value)){
                    m_curr_play.value += player.PRE_INCORRECT;
                    player.set_element_m_player_moves(m_curr_play.row-1, m_curr_play.col-1, m_curr_play.value);
                }
                else{
                    m_curr_play.value += player.PRE_INVALID;
                    player.set_element_m_player_moves(m_curr_play.row-1, m_curr_play.col-1, m_curr_play.value);
                }
            }
            else{
                m_curr_msg = "The value of <row> or <col> is an ORIGINAL value, it cannot be changed";
            }

            m_game_state = game_state_e::PLAYING_MODE;
        }

        // REMOVING_PLAY
        else if(m_game_state == game_state_e::REMOVING_PLAY){
            if (not player.check_original_pos(m_curr_play.row-1, m_curr_play.col-1)){
                // Adiciona a versão na pilha antes que ela seja alterada.
                stack_moves.push(player.get_board_moves());
                player.set_element_m_player_moves(m_curr_play.row-1, m_curr_play.col-1, EMPTY_VALUE);
            }
            else{
                m_curr_msg = "The value of <row> or <col> is an ORIGINAL value, it cannot be changed";
            }

            m_game_state = game_state_e::PLAYING_MODE;
        }

        // CHECKING_MOVES
        else if(m_game_state == game_state_e::CHECKING_MOVES){                
            // Diminui o número de checagens restantes.
            m_checks_left--;
        }

        // UNDOING_PLAY
        else if(m_game_state == game_state_e::UNDOING_PLAY){
            // Verifica se a pilha têm elementos.
            if(stack_moves.empty()){
                m_curr_msg = "There are no previous moves to be undone";
            }
            else{
                player.change_board(stack_moves.top());
                stack_moves.pop();
            }
            m_game_state = game_state_e::PLAYING_MODE;
        }  
        // Verifica se o tabuleiro está completo.
        if(is_complete()){
                m_game_state = game_state_e::FINISHED_PUZZLE;
        }
    }

    // Rederiza o jogo.
    void SudokuGame::render(){
        if(m_game_state == game_state_e::READING_MAIN_OPT){
            // Print do main principal.
            main_screen(player.get_board_moves(), m_curr_msg);
        }
        else if(m_game_state == game_state_e::HELPING){
            // Print das regras do jogo.
            help_sudoku_rules();
            std::string line;
            std::getline(std::cin, line);
        }
        else if(m_game_state == game_state_e::PLAYING_MODE){
            // Print do tabuleiro de ação do jogo.
            action_mode_menu(player.get_board_moves(), m_curr_msg, m_checks_left, m_curr_play.row, m_curr_play.col);
            m_curr_msg = "";
        }
        else if(m_game_state == game_state_e::CHECKING_MOVES){
            // Menu de checking.
            menu_cheking(player.get_board_moves(), m_curr_msg);
        }
        else if(m_game_state == game_state_e::REQUESTING_NEW_GAME){
            // Menu de requesting new game.
            menu_requesting_new_game(player.get_board_moves(), m_curr_msg);
        }
        else if(m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH){
            // Menu de quitting.
            menu_quitting(player.get_board_moves(), m_curr_msg);
        }
        else if(m_game_state == game_state_e::FINISHED_PUZZLE){
            if(m_quiting_game){
                menu_finished(player.get_board_moves(), m_curr_msg);
                m_curr_msg = "";
                m_game_state = game_state_e::STARTING;
            }
           
        }
    }
    
    // Indica se o jogo chegou ao fim.
    bool SudokuGame::game_over(){
        return m_game_over;
    }
    
    // Destrutor.
    SudokuGame::~SudokuGame(){ /* empty */ }

}
