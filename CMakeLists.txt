cmake_minimum_required(VERSION 3.14)

project(educable_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game 
               game.cpp
               educable_engine.cpp)

target_compile_options(game 
                       PRIVATE 
                       -g -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -O3)
