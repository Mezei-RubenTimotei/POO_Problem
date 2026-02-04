cmake_minimum_required(VERSION 3.21)
project(some)

set(CMAKE_CXX_STANDARD 14)

add_executable(some main.cpp Book.cpp Member.cpp Library.cpp)
