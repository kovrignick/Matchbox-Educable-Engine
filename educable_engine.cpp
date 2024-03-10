#include "educable_engine.hpp"

EducableEngine::EducableEngine(std::size_t boxes, std::size_t elements) {
    std::random_device device;
    random_generator_.seed(device());
    //
    std::uniform_int_distribution<size_t> range(10000000, 99999999);
    educable_engine_id = range(random_generator_);
    // 
    std::size_t elements_bk = elements;
    for (std::size_t i = 1; i <= boxes; ++i) {
        for (std::size_t j = 1; j <= elements; ++j) { permanent_memory[i].push_back(j); }
        elements = elements_bk;
    }
}

void EducableEngine::print_permanent_memory() {
    for (auto& [box, elements]: permanent_memory) {
        std::cout << box << ": ";
        for (auto& element: elements) { std::cout << element << " "; }
        std::cout << "\n";
    }
}

void EducableEngine::print_temporary_memory() {
    for (auto& [box, element]: temporary_memory) {
        std::cout << box << ": " << element << " " << std::endl;
    }
}

std::size_t EducableEngine::make_choice(std::size_t box) {
    std::vector<std::size_t> elements = permanent_memory[box];
    std::size_t size = elements.size();
    if (size == 0) {
        std::size_t zero = 0;
        return zero;
    } else {
        std::uniform_int_distribution<size_t> range(0, size - 1);
        std::size_t element = elements[range(random_generator_)];
        temporary_memory[box] = element;
        return element;
    }
}

void EducableEngine::save_temporary_to_permanent() {
    for (auto& [box, element]: temporary_memory) { permanent_memory[box].push_back(element); }
    clear_temporary();
}

void EducableEngine::clear_temporary() {
    std::map<std::size_t, std::size_t> empty;
    std::swap(temporary_memory, empty);
}

void EducableEngine::clear_permanent() {
    std::map<std::size_t, std::vector<std::size_t>> empty;
    std::swap(permanent_memory, empty);
}

void EducableEngine::forget_choises_forever() {
    for (auto& [box, element]: temporary_memory) {
        if (permanent_memory[box].size() > 1) {
            auto it = std::find(permanent_memory[box].begin(), permanent_memory[box].end(), element);
            if (it != permanent_memory[box].end()) {
                permanent_memory[box].erase(it);
            }
        }
    }
    clear_temporary();
}

void EducableEngine::save_memory_to_file() {
    std::string filename = "ee_memory";
    save_memory_to_file(filename);
}

void EducableEngine::save_memory_to_file(std::string& filename) {
    std::ofstream out_file;
    out_file.open(filename); 
    if (out_file.is_open()) {
        for (auto& [box, elements]: permanent_memory) {
            for (auto& element: elements) {
                out_file << element << " ";
            }
            out_file << std::endl;
        }
        out_file.close();
    } else {
        throw std::runtime_error("Incorrect file");
    }
}

void EducableEngine::load_memory_from_file() {
    std::string filename = "ee_memory";
    load_memory_from_file(filename);
}

void EducableEngine::load_memory_from_file(std::string& filename) {
    std::ifstream in_file;
    in_file.open(filename);
    if (in_file.is_open()) {
        clear_permanent();
        std::string line;
        std::size_t box = 0;
        const char* const delimeter = " ";
        while (std::getline(in_file, line)) {
            ++box;
            char* value = std::strtok(line.data(), delimeter);
            while (value != nullptr) {
                std::string value_string = value;
                std::stringstream sstream(value_string);
                std::size_t value_size_t;
                sstream >> value_size_t;
                permanent_memory[box].push_back(value_size_t);
                value = std::strtok(nullptr, delimeter);
            }
        }
    } else {
        throw std::runtime_error("Incorrect file");
    }
}