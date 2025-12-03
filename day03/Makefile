SHELL := /bin/zsh

default: build run

build:
	g++ -static -O0 -std=c++17 -Wall main.cpp -o solution

run:
	cat test_input.txt | time ./solution # 357 | 3121910778619
	cat input.txt | time ./solution

