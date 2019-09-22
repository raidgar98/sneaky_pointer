#!/bin/bash
#primitive make :)
clear && clear
rm run 2>>/dev/null
g++-8 -o run -std=c++17 -w main.cpp sneaky_pointer.hpp
./run 2>>/dev/null
