cmake_minimum_required(VERSION 3.20)
project(Lab0_b)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab0_b main.cpp
        FrequencyCounter.cpp
        FrequencyCounter.h)