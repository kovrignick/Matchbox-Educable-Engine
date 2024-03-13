#include "game.hpp"
#include "educable_engine.hpp"

int main() {
    greeting();
    game_rules();
    std::size_t ITEMS = set_items_quantity();
    std::size_t MAX_PICK = set_max_pick(ITEMS);

    GameTable2Player table{ITEMS, MAX_PICK};
    
    signal(SIGINT, signal_callback_handler);

    int game_mode = select_game_mode();

    switch (game_mode) {
    case 1: {
        std::string pl1_name;
        std::cout << "Player1, please enter your name: ";
        std::cin >> pl1_name;
        PlayerHuman pl1(pl1_name);

        PlayerComputer pl2{ITEMS, MAX_PICK, "EE"};

        play_nim_game(table, pl1, pl2, ITEMS, MAX_PICK);
        break;
        }
    case 2: {
        std::string pl1_name;
        std::cout << "Player1, please enter your name: ";
        std::cin >> pl1_name;
        PlayerHuman pl1(pl1_name);

        std::string pl2_name;
        std::cout << "Player2, please enter your name: ";
        std::cin >> pl2_name;
        PlayerHuman pl2(pl2_name);

        play_nim_game(table, pl1, pl2, ITEMS, MAX_PICK);
        break;
        }
    case 3: {
        PlayerComputer pl1{ITEMS, MAX_PICK, "EE-player1"};
        PlayerComputer pl2{ITEMS, MAX_PICK, "EE-player2"};
        std::size_t rounds;
        std::cout << "Enter the number of rounds the computers will play: ";
        std::cin >> rounds;
        play_nim_game(table, pl1, pl2, ITEMS, MAX_PICK, rounds);
        table.show_game_result();
        break;
        }
    default:
        break;
    }

    return 0;
}