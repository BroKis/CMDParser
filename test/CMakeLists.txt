# � ����������� CMake ������������� ����� �������� ������ ������ CMake.
cmake_minimum_required(VERSION 3.28)

# ������� CMake ��� �� ������.
project(args_parse_test_app LANGUAGES CXX)

# ���������� ���������� ���� � �� ���� �� �������.
add_executable(_unit_test_args_parse main.cpp)

target_link_libraries(_unit_test_args_parse
    PRIVATE
        # ���������� args_parse ������ ���� ������������ � ����� ����������� �����.
        args_parse
        # ���������� Catch2 ������ ���� ������������ � ����� ����������� �����.
        Catch2::Catch2WithMain
)

# ����������� ���� ������� �� �������� CTest, ��� � ��� ���� ��� ���� ����.
catch_discover_tests(_unit_test_args_parse)