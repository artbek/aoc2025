SHELL := /bin/zsh

default: build run

build:
	g++ -static -O1 -std=c++17 -Wall main.cpp -o solution

run:
	cat test_input.txt | time ./solution # 5 | ...
	cat test_input2.txt | time ./solution # 2 | ...
	cat input.txt | time ./solution

