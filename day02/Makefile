SHELL := /bin/zsh

default: build run

build:
	g++ -static -O1 -std=c++17 -Wall main.cpp -o solution

run:
	cat test_input.txt | time ./solution # 1227775554 | 4174379265
	cat input.txt | time ./solution

