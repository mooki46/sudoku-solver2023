#pragma once

#include <chrono>
#include "CellGroup.h"

class SudokuPuzzle
{
public:
	SudokuPuzzle();
	~SudokuPuzzle();

	void load(const char filenameIn[]);
	void solve();
	void output(const char filenameOut[]) const;

	void updateCandidates(int& counter);

	void print() const;

private:
	std::chrono::duration<double, std::micro> _loadTime;
	std::chrono::duration<double, std::micro> _solveTime;
	CellGroup _rows[9];
	CellGroup _columns[9];
	CellGroup _blocks[9];
};

