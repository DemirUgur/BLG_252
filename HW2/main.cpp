#include "Header.h"

void print_grid(const vector<vector<OperatorCenter> >&);

int main() {
	ArithmeticOperator Jeff(3, 3, 2, '+');
	OperatorGrid grid(10, 10);

	grid.place_operator(&Jeff);
	//print_grid(grid.get_grid());
	grid.move_operator(2, 3, 'D', 2);
	//print_grid(grid.get_grid());

	return 0;
}

//DEBUG purposes
/*void print_grid(const vector<vector<OperatorCenter> >& GridToPrint) {
	for (vector<OperatorCenter> i : GridToPrint) {
		for (OperatorCenter k : i) {
			cout << k.sign;
		}
		cout << endl;
	}

	return;
}*/
