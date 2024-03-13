#include "game.hpp"
#include "educable_engine.hpp"

GameTable2Player::GameTable2Player(std::size_t i, std::size_t p)
    : items_{i}
    , items_backup{i}
    , max_pick_{p} {}

std::size_t GameTable2Player::items_on_table() { return items_; }

void GameTable2Player::pick_some_items(std::size_t how_many_items) {
    if (how_many_items > items_) { throw std::logic_error("ItemsError"); };
    items_ -= how_many_items;
}

void GameTable2Player::print_table() {
    for (std::size_t i = 1; i <= items_; ++i) { 
        std::cout << " |";
        if (i > 9) { std::cout << " "; }
        if (i > 99) { std::cout << "  "; }
    }
    std::cout << std::endl;
    for (std::size_t i = 1; i <= items_; ++i) { 
        std::cout << " " << i;
    }
    std::cout << std::endl << std::endl;
}

bool GameTable2Player::table_is_empty() { return items_ == 0; }

void GameTable2Player::reset_table() { items_ = items_backup;}

void GameTable2Player::reset_table(std::size_t items) { items_backup = items_ = items; }

void GameTable2Player::player1_win() { ++player1_wins; }

void GameTable2Player::player2_win() { ++player2_wins; }

void GameTable2Player::next_round() {
    ++round_number;
    reset_table();
}

std::size_t GameTable2Player::player1_win_count() { return player1_wins; }

std::size_t GameTable2Player::player2_win_count() { return player2_wins; }

std::size_t GameTable2Player::round_count() { return round_number; }

void GameTable2Player::show_game_result() { 
    std::cout << "\nTotal rounds - " << round_count();
    std::cout << "\nPlayer1 wins: " << player1_win_count();
    std::cout << "\nPlayer2 wins: " << player2_win_count() << std::endl;
    std::cout << std::endl;
}

bool check_choise(std::size_t choice, std::size_t on_table, std::size_t max, std::size_t min) {
    bool result = false;
    if (choice > on_table) { result = true; }
    if (choice > max) { result = true; }
    if (choice < min) { result = true; }
    return result;
}

std::size_t PlayerHuman::choose_items_to_take(std::size_t items_on_table) {
    std::cout << "Enter how many items do you want to take: ";
    std::size_t item;
    std::cin >> item;
    return item;
}

void PlayerHuman::game_attempt(GameTable2Player& table, std::size_t MAX_PICK, std::size_t MIN_PICK) {
    std::size_t choice;
    bool choice_is_wrong;
    do {
        choice = this->choose_items_to_take(table.items_on_table());
        choice_is_wrong = check_choise(choice, table.items_on_table(), MAX_PICK, MIN_PICK);
    } while (choice_is_wrong);
    table.pick_some_items(choice);
    std::cout << name() << " take " << choice << " items" << "\n" << std::endl;
}

void PlayerHuman::win() {
    std::cout << "The " << name() << " brain won this round." << std::endl;
}

void PlayerHuman::lose() {
    std::cout << name() << ", you lost in this round." << std::endl;
}

PlayerComputer::PlayerComputer(std::size_t i, std::size_t p, std::string name = "EE") 
    : Player{name}, EE{i, p} {};

std::size_t PlayerComputer::choose_items_to_take(std::size_t items_on_table) {
    return EE.make_choice(items_on_table);
}

void PlayerComputer::game_attempt(GameTable2Player& table, std::size_t MAX_PICK, std::size_t MIN_PICK) {
    std::size_t choice;
    bool choice_is_wrong;
    do {
        choice = choose_items_to_take(table.items_on_table());
        choice_is_wrong = check_choise(choice, table.items_on_table(), MAX_PICK, MIN_PICK);
    } while (choice_is_wrong);
    table.pick_some_items(choice);
}

void PlayerComputer::win() {
    EE.save_temporary_to_permanent();
}

void PlayerComputer::lose() {
    EE.forget_choises_forever();
}

void PlayerComputer::print_memory() {
    EE.print_permanent_memory();
}

void PlayerComputer::save() {
    EE.save_memory_to_file();
}
void PlayerComputer::load(std::string& filename) {
    EE.load_memory_from_file(filename);
}

void greeting() {
    std::cout << "Welcome to the game \"Bashe\" (a special case nim game - https://en.wikipedia.org/wiki/Nim )\n" << std::endl;
}

void game_rules() {
    std::cout << "The rules of the game:" << std::endl;
    std::cout << "- there are [N] items on the table;" << std::endl;
    std::cout << "- two players take turns taking from 1 to M items from the table;" << std::endl;
    std::cout << "- the one who has nothing to take from the table has lost.\n" << std::endl;
}

std::size_t set_items_quantity() {
    std::size_t quantity;
    while (true) {
        std::cout << "Enter the number of items that will be on the table [N] = ";
        std::cin >> quantity;
        if ( quantity > 0 && quantity < 1000 ) { break; }
        else { std::cout << "Value must be greater than 0 and less than 1000\n"; }
    }
    return quantity;
}

std::size_t set_max_pick(const std::size_t& items) {
    std::size_t max_pick;
    while (true) {
        std::cout << "Enter the number of maximum items a player can take per turn [M] = ";
        std::cin >> max_pick;
        if ( max_pick > 0 && max_pick < items ) { break; }
        else { std::cout << "Value must be greater than 0 and less than items (" << items << ")\n"; }
    }
    return max_pick;

}

int select_game_mode() {
    int mode = 0;
    std::cout << "Choose the game mode:\n";
    std::cout << "1 - Human vs Computer\n";
    std::cout << "2 - Human vs Human\n";
    std::cout << "3 - Computer vs Computer\n";
    while (true) {
        std::cout << "Enter the number of mode: ";
        std::cin >> mode;
        if ( mode > 0 && mode < 4 ) { break; }
        else { std::cout << "Only 1, 2 or 3\n"; }
    }
    return mode;
}

// void show_game_result(GameTable2Player& table) {
//     std::cout << "\nTotal rounds - "; table.round_count();
//     std::cout << "\nPlayer1 wins: "; table.player1_win_count();
//     std::cout << "\nPlayer2 wins: "; table.player2_win_count();
//     std::cout << std::endl;
// }

void play_nim_game(GameTable2Player& table, Player& player1, Player& player2,
                   std::size_t ITEMS, std::size_t MAX_PICK, 
                   std::size_t last_round, std::size_t MIN_PICK) {
    for (;;) {
        table.next_round();
        if (last_round == 0) {
            std::cout << "Start round #" << table.round_count() << "\n" << std::endl;
        }
        for (;;) {
            if (last_round == 0) { table.print_table(); }
            if (table.round_count() % 2 == 0) {
                player1.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    table.player1_win();
                    player1.win();
                    player2.lose();
                    break;
                }
                if (last_round == 0) { table.print_table(); }
                player2.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    table.player2_win();
                    player2.win();
                    player1.lose();
                    break;
                }
            } else {
                player2.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    table.player2_win();
                    player2.win();
                    player1.lose();
                    break;
                }
                if (last_round == 0) { table.print_table(); }
                player1.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    table.player1_win();
                    player1.win();
                    player2.lose();
                    break;
                }
            }
        }
        if (table.round_count() > last_round) { table.show_game_result(); }
        if (table.round_count() == last_round) { break; }
    }
}

void signal_callback_handler(int signum) {
   std::cout << "\nCaught signal, exit game. " << std::endl;
   exit(signum);
}
