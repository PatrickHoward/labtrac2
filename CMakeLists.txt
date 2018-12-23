cmake_minimum_required(VERSION 3.1)
project(LabTrac)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(labTrac
    Computer.cpp
    ioHandiling.cpp
    Lab.cpp
    Menu.cpp
    projectPartB.cpp
)

