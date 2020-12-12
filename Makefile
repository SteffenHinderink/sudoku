puzzle?=puzzles/hard.txt # sonst make puzzle=puzzles/puzzle.txt

run: build/Sudoku
	./build/Sudoku $(puzzle)

build/Sudoku: build src/Sudoku.cc
	g++ src/Sudoku.cc -o build/Sudoku

build:
	mkdir build

clear:
	rm -rf build
