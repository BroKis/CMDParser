# � ����������� CMake ������������� ����� �������� ������ ������ CMake.
cmake_minimum_required(VERSION 3.28)

# ������� CMake ��� �� ������.
project(scan_directory_main_app LANGUAGES CXX)

# ���������� ���������� ���� � �� ���� �� �������.
add_executable(scan_directory_main main.cpp)

# ���������� args_parse ������ ���� ������������ � ����� ����������� �����.
target_link_libraries(scan_directory_main PRIVATE args_parse directory_and_pool)