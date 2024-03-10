#include "educable_engine.hpp"

class GameTable {
private:
    std::size_t items_;
    std::size_t items_backup;
    std::size_t max_pick_;
public:
    GameTable() = delete;
    GameTable(std::size_t, std::size_t);
    std::size_t items_on_table();
    bool table_is_empty();
    void pick_some_items(std::size_t);
    void print_table();
    void reset_table();
    void reset_table(std::size_t items);
};

bool check_choise(std::size_t, std::size_t, std::size_t, std::size_t);

class Player {
public:
    std::string name();
    std::size_t items_to_take(std::size_t);
    void win();
    void lose();
    void game_attempt(GameTable&, std::size_t, std::size_t);
};

class PlayerEE {
private:
    EducableEngine EE;
public:
    PlayerEE() = delete;
    PlayerEE(std::size_t, std::size_t);

    std::string name();
    std::size_t items_to_take(std::size_t items_on_table);
    void win();
    void lose();
    void print_mem();
    void game_attempt(GameTable&, std::size_t, std::size_t);
    void save();
    void load(std::string&);
};
