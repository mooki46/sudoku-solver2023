#pragma once
#include "Cell.h"

class CellGroup
{
public:
	CellGroup();
	~CellGroup();

	Cell* getCell(int index) const;
	void setCell(int index, Cell* cell);

private:
	Cell* _cells[9];
};

