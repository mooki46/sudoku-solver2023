#pragma once

class Cell
{
public:
	Cell();
	~Cell();

	void setValue(int value);
	int getValue() const;

	void setPredefined(bool isPredefined);
	bool isPredefined() const;

	void setCandidate(int index, int candidate);
	int getCandidate(int index) const;

	void setSolved(bool solved);
	bool isSolved() const;

private:
	int _value;
	bool _predefined;
	int _candidates[9];
	bool _solved;
};

