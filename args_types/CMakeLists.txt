# ¬ современном CMake рекомендуетс€ сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# √оворим CMake что за проект.
project(args_types_library LANGUAGES CXX)


# ќпредел€ем библиотеку и указываем из чего она состоит.
add_library(args_types STATIC args_types.cpp args_types.hpp)

target_include_directories(args_types PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(args_types PUBLIC cxx_std_17)