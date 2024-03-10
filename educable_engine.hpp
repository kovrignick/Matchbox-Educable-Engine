#pragma once
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

class EducableEngine {
private:
    std::map<std::size_t, std::vector<std::size_t>> permanent_memory;
    std::map<std::size_t, std::size_t> temporary_memory;
    std::mt19937 random_generator_;
    std::size_t educable_engine_id;
    void clear_permanent();
public:
    EducableEngine() = delete;
    EducableEngine(std::size_t, std::size_t);

    void print_permanent_memory();
    void print_temporary_memory();

    std::size_t make_choice(std::size_t);

    void save_temporary_to_permanent();
    void clear_temporary();

    void forget_choises_forever();

    void save_memory_to_file();
    void save_memory_to_file(std::string&);
    void load_memory_from_file();
    void load_memory_from_file(std::string&);
};