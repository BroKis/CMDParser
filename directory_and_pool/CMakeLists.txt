# � ����������� CMake ������������� ����� �������� ������ ������ CMake.
cmake_minimum_required(VERSION 3.28)

# ������� CMake ��� �� ������.
project(directory_and_pool_library LANGUAGES CXX)

# ���������� ���������� � ��������� �� ���� ��� �������.
add_library(directory_and_pool STATIC directory_file.hpp directory_file.cpp thread_pool.hpp thread_pool.cpp executor.hpp)

target_include_directories(directory_and_pool PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(directory_and_pool PUBLIC cxx_std_17)