# ¬ современном CMake рекомендуетс€ сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# √оворим CMake что за проект.
project(args_parse_library LANGUAGES CXX)

# ќпредел€ем библиотеку и указываем из чего она состоит.
add_library(args_parse STATIC abstract_arg.hpp args.hpp  args_error.hpp args_validator.hpp single_arg.hpp utils.cpp utils.hpp multi_arg.hpp user_types.hpp)

target_include_directories(args_parse PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(args_parse PUBLIC cxx_std_17)