#include "Cell.h"

Cell::Cell() :
		row(0), col(0) {
}

Cell::Cell(int32_t _row, int32_t _col) :
		row(_row), col(_col) {
}

bool Cell::operator==(const Cell &cell) const {
	return row == cell.row && col == cell.col;
}

bool Cell::operator!=(const Cell &cell) const {
	return !(*this == cell);
}

const Cell Cell::UNDEFINED(10000, 10000);

std::ostream& operator<<(std::ostream &os, const Cell &cell) {
	return os << "Row: " << cell.row << "; " << "Col: " << cell.col;
}

Cell& Cell::moveTop() {
	this->row--;

	return *this;
}

Cell& Cell::moveRight() {
	this->col++;

	return *this;
}

Cell& Cell::moveDown() {
	this->row++;

	return *this;
}

Cell& Cell::moveLeft() {
	this->col--;

	return *this;
}
