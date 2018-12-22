cmake_minimum_required(VERSION 3.1)
project(LabTrac)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(labTrac 
                ioHandiling.cpp
                projectPartB.cpp
                Computer.cpp
                Lab.cpp
              )

