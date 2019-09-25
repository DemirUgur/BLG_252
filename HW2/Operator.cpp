#include "Header.h"

Operator::Operator(int x, int y, int size) {
	//cout << "Operator Constructor!" << endl;
	center_x = x;
	center_y = y;
	op_size = size;
}

int Operator::get_x() { return center_x; }
int Operator::get_y() { return center_y; }
int Operator::get_size() { return op_size; }

void Operator::set_x(int x) { center_x = x; }
void Operator::set_y(int y) { center_y = y; }
void Operator::set_size(int size) { op_size = size; }

void Operator::reset(int new_x, int new_y, int new_size) {
	center_x = new_x;
	center_y = new_y;
	op_size = new_size;
	return;
}