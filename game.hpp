#include <signal.h>
#include "educable_engine.hpp"

class GameTable2Player {
private:
    std::size_t items_;
    std::size_t items_backup;
    std::size_t max_pick_;
    
    std::size_t player1_wins = 0;
    std::size_t player2_wins = 0;
    std::size_t round_number = 0;
public:
    GameTable2Player() = delete;
    GameTable2Player(std::size_t, std::size_t);
    std::size_t items_on_table();
    bool table_is_empty();
    void pick_some_items(std::size_t);
    void print_table();
    void reset_table();
    void reset_table(std::size_t items);
    void player1_win();
    void player2_win();
    void next_round();
    std::size_t player1_win_count();
    std::size_t player2_win_count();
    std::size_t round_count();
    void show_game_result();
};

bool check_choise(std::size_t, std::size_t, std::size_t, std::size_t);

class Player {
private:
    std::string player_name;
public:
    Player(std::string name) : player_name(name) {}
    std::string name() { return player_name; }
    virtual std::size_t choose_items_to_take(std::size_t) = 0;
    virtual void game_attempt(GameTable2Player&, std::size_t, std::size_t) = 0;
    virtual void win() = 0;
    virtual void lose() = 0;
};

class PlayerHuman : public Player {
public:
    PlayerHuman(std::string name = "Human")
        : Player{name} {}

    std::size_t choose_items_to_take(std::size_t) override;

    void game_attempt(GameTable2Player&, std::size_t, std::size_t) override;

    void win() override;

    void lose() override;
};

class PlayerComputer : public Player  {
private:
    EducableEngine EE;
public:
    PlayerComputer() = delete;
    PlayerComputer(std::size_t, std::size_t, std::string);

    std::size_t choose_items_to_take(std::size_t items_on_table) override;

    void game_attempt(GameTable2Player&, std::size_t, std::size_t) override;

    void win() override;

    void lose() override;

    void print_memory();

    void save();
    void load(std::string&);
};


void greeting();

void game_rules();

std::size_t set_items_quantity();

std::size_t set_max_pick(const std::size_t&);

int select_game_mode();

void play_nim_game(GameTable2Player&, Player&, Player&,
                   std::size_t, std::size_t, 
                   std::size_t last_round = 0, std::size_t MIN_PICK = 1);

void signal_callback_handler(int);
