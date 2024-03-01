#pragma once
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <vector>
#include <map>

class EducableEngine {
private:
    std::map<std::size_t, std::vector<std::size_t>> permanent_memory;
    std::map<std::size_t, std::size_t> temporary_memory;
    std::mt19937 random_generator_;
public:
    EducableEngine() = delete;
    EducableEngine(std::size_t, std::size_t);

    void print_permanent_memory();
    void print_temporary_memory();

    std::size_t make_choice(std::size_t);

    void save_temporary_to_permanent();
    void clear_temporary();

    void forget_choises_forever();
};