#include "SudokuPuzzle.h"
#include <iostream>
#include <fstream>
#include <chrono>

//sing namespace std;

SudokuPuzzle::SudokuPuzzle() :
	_loadTime (std::chrono::duration<double>(0)),
	_solveTime(std::chrono::duration<double>(0)) {
}

SudokuPuzzle::~SudokuPuzzle()
{
	std::cout << "Time to load: " << _loadTime.count() << " microseconds" << std::endl;
	std::cout << "Time to solve: " << _solveTime.count() << " microseconds" << std::endl;

}

void SudokuPuzzle::load(const char filenameIn[]) {
	const auto start = std::chrono::high_resolution_clock::now();

	std::ifstream file(filenameIn);

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file");
		return;
	}

	int value;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			file >> value;

			Cell* cell = new Cell();
			cell->setValue(value);

			if (value > 0)
			{
				cell->setPredefined(true);
				for (int i = 0; i < 9; i++)
				{
					cell->setCandidate(i, 0);
				}
			}

			_rows[row].setCell(col, cell);
			_columns[col].setCell(row, cell);

			int block = (row / 3) * 3 + (col / 3);
			_blocks[block].setCell((row % 3) * 3 + (col % 3), cell);
		}
	}

	file.close();

	const auto end = std::chrono::high_resolution_clock::now();
	_loadTime = end - start;
}

void SudokuPuzzle::solve() {
	const auto start = std::chrono::high_resolution_clock::now();

	// Add your code here to solve the puzzle
	int numSolvedCells = 0;
	int numPasses = 0;
	int numCandidatesConsidered = 0;

	updateCandidates(numCandidatesConsidered);

	bool solved = false;
	do {
		solved = true;
		numPasses++;
		int cellsSolvedThisPass = 0;

		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				Cell* cell = _rows[row].getCell(col);
				if(!cell->isPredefined())
				{
					if (cell->getValue() == 0)
					{
						solved = false;

						updateCandidates(numCandidatesConsidered);

						int numCandidates = 0; 
						int value = 0;
						for (int i = 0; i < 9; i++)
						{
							if (cell->getCandidate(i) > 0)
							{
								numCandidates++;
								value = i + 1;
							}
						}

						if (numCandidates == 1)
						{
							cell->setValue(value);
							numSolvedCells++;
							cellsSolvedThisPass++;
						}
					}
				}
			}
		}
		if (cellsSolvedThisPass == 0 && solved == false)
		{
			solved = false;
			break;
		}

	} while (!solved);

	std::string result;
	if (solved)
	{
		result = "True";
	}
	else
	{
		result = "False";
	}
	std::cout << "Puzzle solved: " << result << std::endl;
	std::cout << "Passes: " << numPasses << std::endl;
	std::cout << "Solved cells: " << numSolvedCells << std::endl;
	std::cout << "Candidates considered: " << numCandidatesConsidered << std::endl;
	const auto end = std::chrono::high_resolution_clock::now(); 
	_solveTime = end - start;
}

// This is an example of how you may output the solved puzzle
void SudokuPuzzle::output(const char filenameOut[]) const {

	// Add your code here to write your solution to the file filenameOut
	std::ofstream file(filenameOut);

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open or create file");
		return;
	}
	for (int row = 0; row < 9; row++) //writes the grid into a new file
	{
		for (int col = 0; col < 9; col++)
		{
			int value = _rows[row].getCell(col)->getValue();
			file << value << " ";
		}
		if (row < 8)
		{
			file << std::endl;
		}
	}

	file.close();
}

void SudokuPuzzle::print() const {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			int value = _rows[row].getCell(col)->getValue();
			std::cout << value << " ";
			if ((col + 1) % 3 == 0 && col != 8) {
				std::cout << "| ";
			}
		}
		std::cout << std::endl;
		if ((row + 1) % 3 == 0 && row != 8) {
			std::cout << "------+-------+------" << std::endl;
		}
	}
}

void SudokuPuzzle::updateCandidates(int& candidateConsidered)
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			Cell* cell = _rows[row].getCell(col);

			//skip predefined cells
			if (!cell->isPredefined())
			{
				for (int i = 0; i < 9; i++)
				{
					Cell* nextCell = _rows[row].getCell(i);
					int value = nextCell->getValue();
					if (value != 0)
					{
						cell->setCandidate(value - 1, false); //sets the candidate 0
						candidateConsidered++;
					}

					nextCell = _columns[col].getCell(i);
					value = nextCell->getValue();
					if (value != 0)
					{
						cell->setCandidate(value - 1, false); //sets the candidate 0
						candidateConsidered++;
					}

					nextCell = _blocks[(row / 3) * 3 + (col / 3)].getCell(i);
					value = nextCell->getValue();
					if (value != 0)
					{
						cell->setCandidate(value - 1, false); //sets the candidate 0
						candidateConsidered++;
					}
				}
			}
			
		}
	}

}
