#include "Header.h"

//checks for a char in a string
bool isIn(string dst, char src) {
	for (unsigned int i = 0; i < dst.size(); i++) {
		if (dst[i] == src) {
			return true;
		}
	}
	return false;
}

ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign)
{
	//Checks for correct sign input
	string test = "+-/x";
	if (!isIn(test, sign)) {
		cout << "SIGN parameter is invalid!";
		return;
	}
	set_x(x);
	set_y(y);
	set_size(size);
	this->sign = sign;
}

void ArithmeticOperator::print_operator()
{
	const int x = get_x();
	const int y = get_y();
	const int size = get_size();

	printf("ARITHMETIC_OPERATOR[%c], CENTER_LOCATION[%d,%d], SIZE[%d]\n", sign, x, y, size);
	return;
}
