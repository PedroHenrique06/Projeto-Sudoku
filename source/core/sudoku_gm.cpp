#include <cassert>
#include <stdexcept>
#include <iterator>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "sudoku_gm.h"
#include "board_treatment.h"
#include "print.h"

// Função para dividir uma string em várias partes
std::vector<std::string> split(const std::string & input_str, char delimiter=' '){
    // Store the tokens.
    std::vector<std::string> tokens;
    // read tokens from a string buffer.
    std::istringstream iss;
    iss.str(input_str);
    // This will hold a single token temporarily.
    std::string token;
    while (std::getline(iss >> std::ws, token, delimiter))
        tokens.emplace_back(token);
    return tokens;
}


namespace sdkg {

    // Expressão lambda que transforma uma string em minúscula
    auto STR_LOWERCASE = [](const char * t)->std::string{
        std::string str{ t };
        std::transform( str.begin(), str.end(), str.begin(), ::tolower );
        return str;
    };

    // Função lambda para testar se o valor é um número
    auto IS_DIGIT = [](std::string number)->bool{
        if(all_of(number.begin(), number.end(), [](char digit)->bool{ return isdigit(digit); })){
            return true;
        }
        return false;
     };

    // Construtor padrão
    SudokuGame::SudokuGame(){
        m_opt.total_checks = 3; // Valor padrão
        m_opt.input_filename = "../../data/input.txt"; // Valor padrão.
    }

    void SudokuGame::initialize(int argc, char** argv){
        //Tratamento dos argumentos da linha de comando
        if(argc == 2 ){
            if(std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") usage("");
            // Testa se o argumento é [-c], caso seja, acusa falta de complemtento
            else if(std::string(argv[1]) == "-c") usage(Color::tcolor("Lacking complement of argument", Color::YELLOW, Color::REGULAR));
            else{
                m_opt.input_filename = argv[1];
            }
        }
        else if(argc == 3){
            if(std::string(argv[1]) == "-c"){
            // Testa se após [-c] há um número
                if(IS_DIGIT(std::string(argv[2]))){
                    m_opt.total_checks = std::stoi(std::string(argv[2]));
                }
                else usage(Color::tcolor("The complement of the -c has to be an integer", Color::YELLOW, Color::REGULAR));
            }
        }
        else if(argc == 4){
            if(std::string(argv[1]) == "-c"){
                // Testa se após [-c] há um número
                if(IS_DIGIT(std::string(argv[2]))){
                    m_opt.total_checks = std::stoi(std::string(argv[2])); 
                    m_opt.input_filename = argv[3];
                }
                else usage("The complement of the -c has to be an integer");
            }    
        }
    fill_data_base_puzzles(*this);
    }

    void SudokuGame::display_welcome(){
        std::cout << "\n==================================================================\n" 
                  << "\tWelcome to a terminal version of Sudoku, v1.0\n"
                  << "\tCopyright (C) 2020, Selan R. dos Santos\n"
                  << "==================================================================\n"
                  << "\nPress enter to start.";
    }

    void SudokuGame::usage( std::string msg ) const{
        if ( msg != "" ) std::cerr << "sudoku: " << msg << "\n\n";

        std::cerr << "Usage: sudoku [-c <num>] [--help] <input_puzzle_file>\n"
                  << "  Game options:\n"
                  << "    -c     <num> Number of checks per game. Default = 3.\n"
                  << "    --help       Print this help text.\n";
        std::cerr << std::endl;

        exit( msg != "" ? 1 : 0 );
    }

    void SudokuGame::process_events(){
        if ( m_game_state == game_state_e::STARTING or
             m_game_state == game_state_e::HELPING  or
             m_game_state == game_state_e::CHECKING_MOVES or
             m_game_state == game_state_e::FINISHED_PUZZLE )
        {
            
            if(m_game_state == game_state_e::CHECKING_MOVES)
                m_game_state = game_state_e::PLAYING_MODE;
            else
                m_game_state = game_state_e::READING_MAIN_OPT;
            
            // Mantém a tela pausada até que o usuário precione enter
            std::string line;
            std::getline(std::cin, line);    
        }
        else if ( m_game_state == game_state_e::READING_MAIN_OPT ){

            // Print do main principal
            main_screen(available_puzzles[off_set_board], m_curr_msg);

            std::string line;
            
            std::string option;
            // Captura da opção escolhida
            std::cin >> option;

            // Teste para checar se é um número
            if(IS_DIGIT(option)){
                m_curr_main_menu_opt = main_menu_opt_e(std::stoi(option));
                // Teste para checar se está no intervalo válido de opções
                if( std::stoi(option) <= 0 or std::stoi(option) > 4 ){
                    WARNING("The value is outside of the valid range of options");
                }
            }
            else{
                WARNING("The entry has to be a number");
            }
            
            if(m_curr_main_menu_opt == main_menu_opt_e::PLAY){
                m_game_state = game_state_e::PLAYING_MODE;
            }
            else if(m_curr_main_menu_opt == main_menu_opt_e::NEW_GAME){
                //Muda o tabuleiro que é mostrado no menu principal
                new_game_board++;
                off_set_board = new_game_board % available_puzzles.size();
            }
            else if(m_curr_main_menu_opt == main_menu_opt_e::QUIT){
                // Testar se há um jogo em curso passar para o QUITTING_MATCH 
                // TODO

                m_game_state = game_state_e::CONFIRMING_QUITTING_MATCH;
            }
            else if(m_curr_main_menu_opt == main_menu_opt_e::HELP){
                help_sudoku_rules();
                std::string line;
                std::getline(std::cin, line); 
            }  
        }
        else if ( m_game_state == game_state_e::PLAYING_MODE ){
            action_mode_menu(available_puzzles[off_set_board]);
            std::string op;
            std::istringstream iss;
            
            //COMO EU VOU PEGAR A LINHA INTEIRA?
            while (std::getline(std::cin, op));
            
            //COMO VOU FAZER PRO CASO DO ENTER SOZINHO? 
            // TODO

            std::vector<std::string> line = split(op, ' ');

            if(line.empty()){
                m_game_state = game_state_e::READING_MAIN_OPT;
            }
            else{
                std::cout << "COMANDO ACIONADO" << std::endl;
            }
        }
        else if ( m_game_state == game_state_e::CONFIRMING_QUITTING_MATCH ){
            char exit;
        
            m_curr_msg = Color::tcolor("Are you sure you want to leave this game?", Color::BRIGHT_YELLOW, Color::REVERSE);
            main_screen(available_puzzles[off_set_board], m_curr_msg);
            std::cout << "\nYour choise [y/n] > ";
            // Captura da resposta
            std::cin >> exit;
            if(exit == 'y' or exit == 'Y'){
                m_game_over = true;
                game_over();
            }
            else{
                m_curr_msg = "";
                m_game_state = game_state_e::READING_MAIN_OPT;
            }
        }
    }

    void SudokuGame::update(){

    }

    void SudokuGame::render() const{

    }
    
    bool SudokuGame::game_over(){
        return m_game_over;
    }
    
    SudokuGame::~SudokuGame(){ /* empty */ }

}
