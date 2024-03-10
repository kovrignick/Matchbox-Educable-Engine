#include "game.hpp"
#include "educable_engine.hpp"

GameTable::GameTable(std::size_t i, std::size_t p)
    : items_{i}
    , items_backup{i}
    , max_pick_{p} {}
    
std::size_t GameTable::items_on_table() { return items_; }
    
void GameTable::pick_some_items(std::size_t how_many_items) {
    if (how_many_items > items_) { throw std::logic_error("ItemsError"); };
    items_ -= how_many_items;
}

void GameTable::print_table() {
    for (std::size_t i = 1; i <= items_; ++i) { 
        std::cout << " |";
        if (i > 9) { std::cout << " "; }
        if (i > 99) { std::cout << "  "; }
        if (i % 25 == 0) { std::cout << std::endl; }
    }
    std::cout << std::endl;
    for (std::size_t i = 1; i <= items_; ++i) { 
        std::cout << " " << i;
        if (i % 25 == 0) { std::cout << std::endl; }
    }
    std::cout << std::endl << std::endl;
}

bool GameTable::table_is_empty() { return items_ == 0; }

void GameTable::reset_table() { items_ = items_backup;}

void GameTable::reset_table(std::size_t items) { items_backup = items_ = items; }

bool check_choise(std::size_t choice, std::size_t on_table, std::size_t max, std::size_t min) {
    bool result = false;
    if (choice > on_table) { result = true; }
    if (choice > max) { result = true; }
    if (choice < min) { result = true; }
    return result;
}

std::string Player::name() { return "Human"; };
std::size_t Player::items_to_take(std::size_t items_on_table) {
    std::cout << "Enter how many items do you want to take: ";
    std::size_t item;
    std::cin >> item;
    return item;
};
void Player::win() {
    std::cout << "The Human brain won this round." << std::endl;
};
void Player::lose() {
    std::cout << "The Computer won!" << std::endl;
};
void Player::game_attempt(GameTable& table, 
                    std::size_t MAX_PICK, std::size_t MIN_PICK) {
    std::size_t choice;
    bool choice_is_wrong;
    do {
        choice = this->items_to_take(table.items_on_table());
        choice_is_wrong = check_choise(choice, table.items_on_table(), MAX_PICK, MIN_PICK);
    } while (choice_is_wrong);
    table.pick_some_items(choice);
    std::cout << name() << " take " << choice << " items" << "\n" << std::endl;
};

PlayerEE::PlayerEE(std::size_t i, std::size_t p) : EE{i, p} {};

std::string PlayerEE::name() { return "EE"; };
std::size_t PlayerEE::items_to_take(std::size_t items_on_table) {
    return EE.make_choice(items_on_table);
};
void PlayerEE::win() {
    EE.save_temporary_to_permanent();
};
void PlayerEE::lose() {
    EE.forget_choises_forever();
};
void PlayerEE::print_mem() {
    EE.print_permanent_memory();
};
void PlayerEE::game_attempt(GameTable& table, 
                    std::size_t MAX_PICK, std::size_t MIN_PICK) {
    std::size_t choice;
    bool choice_is_wrong;
    do {
        choice = items_to_take(table.items_on_table());
        choice_is_wrong = check_choise(choice, table.items_on_table(), MAX_PICK, MIN_PICK);
    } while (choice_is_wrong);
    table.pick_some_items(choice);
    // std::cout << name() << " take " << choice << " items" << "\n" << std::endl;
};
void PlayerEE::save() {
    EE.save_memory_to_file();
};
void PlayerEE::load(std::string& filename) {
    EE.load_memory_from_file(filename);
};

template <typename T, typename B>
extern void play_nim_game(GameTable& table, T& player1, B& player2,
                   std::size_t ITEMS, std::size_t MAX_PICK, std::size_t MIN_PICK) {
    std::size_t player1_wins = 0;
    std::size_t player2_wins = 0;
    
    std::size_t round_count = 0;
    for (;;) {
        ++round_count;
        std::cout << "Start round #" << round_count << "\n" << std::endl;
        for (;;) {
            table.print_table();
            if (round_count % 2 == 0) {
                player1.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    player1.win();
                    ++player1_wins;
                    player2.lose();
                    break;
                }
                table.print_table();
                player2.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    player2.win();
                    ++player2_wins;
                    player1.lose();
                    break;
                }
            } else {
                player2.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    player2.win();
                    ++player2_wins;
                    player1.lose();
                    break;
                }
                table.print_table();
                player1.game_attempt(table, MAX_PICK, MIN_PICK);
                if (table.table_is_empty()) {
                    player1.win();
                    ++player1_wins;
                    player2.lose();
                    break;
                }
            }
        }
        table.reset_table();
        if (round_count % 80 == 0) {
        std::cout << std::endl;
        std::cout << "Total rounds " << round_count << std::endl;
        std::cout << player1.name() << " wins: " << player1_wins << std::endl;
        std::cout << player2.name() << " wins: " << player2_wins << std::endl;
        std::cout << std::endl;


        // std::cout << "==================================" << std::endl;
        // player1.print_mem();
        // std::cout << "==================================" << std::endl;
        // player2.print_mem();
        // std::cout << "==================================" << std::endl;
        // player1.save();
        break;
        std::string a;
        std::cin >> a;
        }
    }
}

int main() {
    std::size_t ITEMS = 11;
    std::size_t MAX_PICK = 2;
    std::size_t MIN_PICK = 1;
    
    GameTable table{ITEMS, MAX_PICK};
    
    // Player player1;    
    PlayerEE player1{ITEMS, MAX_PICK};
    // player1.save();
    std::string file = "ee_memory11";
    // player1.load(file);
    // player1.print_mem();

    PlayerEE player2{ITEMS, MAX_PICK};
    // Player player2;

    std::cout << "==================================" << std::endl;
    player2.print_mem();
    std::cout << "==================================" << std::endl;

    play_nim_game(table, player1, player2, ITEMS, MAX_PICK, MIN_PICK);
    
    std::cout << "==================================" << std::endl;
    player2.print_mem();
    std::cout << "==================================" << std::endl;
    

    return 0;
}