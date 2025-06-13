#include "SudokuPuzzle.h"
#include <iostream>

using namespace std;

// You should not need to change any code in this file

int main(int argc, char **) {

	{
		SudokuPuzzle puzzle;
		puzzle.load("sudoku_puzzle.txt");
		puzzle.solve();
		puzzle.output("sudoku_solution.txt");
		puzzle.print();
	}

	return 0;
}
