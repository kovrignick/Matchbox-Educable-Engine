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
private:
    std::string player_name;
public:
    Player(std::string name) : player_name(name) {}
    std::string name() { return player_name; }
    virtual std::size_t choose_items_to_take(std::size_t) = 0;
    virtual void game_attempt(GameTable&, std::size_t, std::size_t) = 0;
    virtual void win() = 0;
    virtual void lose() = 0;
};

class PlayerHuman : public Player {
public:
    PlayerHuman(std::string name = "Human")
        : Player{name} {}

    std::size_t choose_items_to_take(std::size_t) override;

    void game_attempt(GameTable&, std::size_t, std::size_t) override;

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

    void game_attempt(GameTable&, std::size_t, std::size_t) override;

    void win() override;

    void lose() override;

    void print_memory();

    void save();
    void load(std::string&);
};
