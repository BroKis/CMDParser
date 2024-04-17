# В современном CMake рекомендуется сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# Говорим CMake что за проект.
project(scan_directory_main_app LANGUAGES CXX)

# Определяем исполнимый файл и из чего он состоит.
add_executable(scan_directory_main main.cpp)

# Библиотека args_parse должна быть прилинкована к этому исполнимому файлу.
target_link_libraries(scan_directory_main PRIVATE args_parse directory_and_pool)