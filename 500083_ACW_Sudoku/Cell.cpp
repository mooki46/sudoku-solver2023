#include "Cell.h"
Cell::Cell()
{
	_value = 0;
	_predefined = false;
	for (int i = 0; i < 9; i++)
	{
		_candidates[i] = i + 1;
	}
	_solved = false;
}

Cell::~Cell() {}

int Cell::getValue() const
{
	return _value;
}
void Cell::setValue(int value)
{
	_value = value;
}

bool Cell::isPredefined() const
{
	return _predefined;
}
void Cell::setPredefined(bool value)
{
	_predefined = value;
}

int Cell::getCandidate(int index) const
{
	return _candidates[index];
}
void Cell::setCandidate(int index, int candidate)
{
	_candidates[index] = candidate;
}

void Cell::setSolved(bool solved)
{
	_solved = solved;
}
bool Cell::isSolved() const
{
	return _solved;
}