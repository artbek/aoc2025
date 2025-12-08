SHELL := /bin/zsh

default: build run

build:
	g++ -static -O0 -std=c++17 -Wall main.cpp -o solution

run:
	cat test_input.txt | time ./solution --test-input # 40 | 25272
	cat input.txt | time ./solution

