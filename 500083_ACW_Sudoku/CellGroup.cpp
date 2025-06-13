#include "CellGroup.h"
CellGroup::CellGroup()
{
	for (int i = 0; i < 9; i++)
	{
		_cells[i] = nullptr;
	}
}

CellGroup::~CellGroup() 
{
	for (int i = 0; i < 9; i++)
	{
		_cells[i] = nullptr;
		delete _cells[i];
	}
}

void CellGroup::setCell(int index, Cell* cell)
{
	_cells[index] = cell;
}

Cell* CellGroup::getCell(int index) const
{
	return _cells[index];
}
