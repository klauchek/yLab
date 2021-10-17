cmake_minimum_required(VERSION 3.16.3)
project(LFU_cache VERSION 1.0)

set (COMPILER_SETTINGS -Wall -Wextra -O2)  

add_executable (LFU_cache 
main.cpp
lfu.h)
