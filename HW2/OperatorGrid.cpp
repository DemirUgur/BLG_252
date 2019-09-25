#include "Header.h"

void remove_operator(vector<vector<OperatorCenter> >& grid, int centerX, int centerY);
void print_grid(const vector<vector<OperatorCenter> >& GridToPrint);

/*****************************
@param x: Placed X coordinate or new X coordinate if sign is moved
@param y: Placed Y coordinate or new Y coordinate if sign is moved
@param moveX: Old X coordinates of a moved sign
@param moveY: Old Y coordinates of a moved sign
******************************/
void conflict_error_massage(const int &x, const int &y, const int size, const char sign, char operation = 'P', int moveX = 0, int moveY = 0) {
	if (operation == 'P')
		printf("CONFLICT ERROR : Operator %c with size %d can not be placed on (%d, %d).\n", sign, size, x, y);
	else
		printf("CONFLICT ERROR: %c can not be moved from (%d,%d) to (%d,%d).", sign, moveX, moveY, x, y);
}
void border_error_massage(const int &x, const int &y, const int size, const char sign, char operation = 'P', int moveX = 0, int moveY = 0) {
	if (operation == 'P')
		printf("BORDER ERROR : Operator %c with size %d can not be placed on (%d, %d).\n", sign, size, x, y);
	else
		printf("BORDER ERROR: %c can not be moved from (%d,%d) to (%d,%d).", sign, moveX, moveY, x, y);
}
void success_message(const int &x, const int &y, const int size, const char sign, char operation = 'P', int moveX = 0, int moveY = 0) {
	if (operation == 'P')
		printf("SUCCESS: Operator %c with size %d is placed on (%d,%d).\n", sign, size, x, y);
	else
		printf("SUCCESS: %c moved from (%d, %d) to (%d, %d).\n", sign, moveX, moveY, x, y);
}

OperatorGrid::OperatorGrid(int rows, int cols)
{
	num_operators = 0;
	grid_cols = cols;
	grid_rows = rows;
	CenterHolder.resize(rows);
	for(int i = 0; i < rows; i++){
        CenterHolder[i].resize(cols);
	}
	/*for (vector<OperatorCenter> &i : CenterHolder) {
		i.resize(cols);
	}*/
}


OperatorGrid::~OperatorGrid()
{
	//since there is nothing to free.
	printf("DESTRUCTOR: GIVE BACK[%d,%d] chars.\n",grid_rows, grid_cols);
	printf("DESTRUCTOR: GIVE BACK[%d] operators.\n", num_operators);
}


vector<vector<OperatorCenter> > OperatorGrid::get_grid()
{
	return CenterHolder;
}


bool OperatorGrid::place_operator(ArithmeticOperator * toPlace, char oper, int moveX, int moveY)
{

	char sign;
	sign = toPlace->get_sign();

	bool placed = false;
	switch (sign) {
	case '+':
		placed = place_plus(toPlace, oper, moveX, moveY);
		break;
	case'-':
		placed = place_minus(toPlace, oper, moveX, moveY);
		break;
	case'x':
		placed = place_multiplication(toPlace, oper, moveX, moveY);
		break;
	case'/':
		placed = place_division(toPlace, oper, moveX, moveY);
		break;
	}
	if (placed == true and oper == 'P') {
		operators[num_operators] = toPlace;
		num_operators++;
		return true;
	}
	return false;
}

bool OperatorGrid::place_plus(ArithmeticOperator *toPlace, char oper, int moveX, int moveY)
{
	int centerX, centerY, opSize;
	centerX = toPlace->get_x();
	centerY = toPlace->get_y();
	opSize = toPlace->get_size();

	//border error check
	if ((centerX - opSize <= 0) || (centerY - opSize <= 0) || (centerX + opSize > grid_cols) || (centerY + opSize > grid_rows))
	{
		border_error_massage(centerX, centerY, opSize, '+', oper, moveX, moveY);
		return false;
	}
	int x = centerX - 1; //array x
	int y = centerY - 1; //array y
	vector<vector<OperatorCenter> > TestGrid = get_grid();

	//conflict error check
	if (TestGrid[y][x].sign != '0') {
		conflict_error_massage(centerX, centerY, opSize, '+',oper, moveX, moveY);
		return false;
	}

	for (int i = 1; i < opSize + 1; i++) {
		if (TestGrid[y][x + i].sign + TestGrid[y][x - i].sign + TestGrid[y + i][x].sign + TestGrid[y - i][x].sign != 4 * '0') {
			conflict_error_massage(centerX, centerY, opSize, '+', oper, moveX, moveY);
			return false;
		}
	}

	//No errors we can place.
	CenterHolder[y][x].changeValues(centerX, centerY, '+',opSize);
 	//grid[y][x] = '+';
	for (int i = 1; i < opSize + 1; i++) {
		CenterHolder[y][x + i].changeValues(centerX, centerY, '+', opSize);
		CenterHolder[y][x - i].changeValues(centerX, centerY, '+', opSize);
		CenterHolder[y + i][x].changeValues(centerX, centerY, '+', opSize);
		CenterHolder[y - i][x].changeValues(centerX, centerY, '+', opSize);
		//grid[y][x + i] = '+';
		//grid[y][x - i] = '+';
		//grid[y + i][x] = '+';
		//grid[y - i][x] = '+';
	}
	success_message(centerX, centerY, opSize, '+', oper, moveX, moveY);
	return true;
}

bool OperatorGrid::place_minus(ArithmeticOperator *toPlace, char oper, int moveX, int moveY)
{
	int centerX, centerY, opSize;
	centerX = toPlace->get_x();
	centerY = toPlace->get_y();
	opSize = toPlace->get_size();

	if ((centerX - opSize <= 0) || (centerX + opSize > grid_cols))
	{
		border_error_massage(centerX, centerY, opSize, '-', oper);
		return false;
	}
	int x = centerX - 1;
	int y = centerY - 1;
	vector<vector<OperatorCenter> > TestGrid = get_grid();
	if (TestGrid[y][x].sign != '0') {
		conflict_error_massage(centerX, centerY, opSize, '-', oper);
		return false;
	}

	for (int i = 1; i < opSize + 1; i++) {
		if (TestGrid[y][x + i].sign + TestGrid[y][x - i].sign  != 2 * '0') {
			conflict_error_massage(centerX, centerY, opSize, '-', oper);
			return false;
		}
	}

	//No errors we can place.
	CenterHolder[y][x].changeValues(centerX, centerY, '-', opSize);
	//grid[y][x] = '+';
	for (int i = 1; i < opSize + 1; i++) {
		CenterHolder[y][x + i].changeValues(centerX, centerY, '-', opSize);
		CenterHolder[y][x - i].changeValues(centerX, centerY, '-', opSize);
		//grid[y][x + i] = '+';
		//grid[y][x - i] = '+';
	}
	success_message(centerX, centerY, opSize, '-', oper);
	return true;
}

bool OperatorGrid::place_multiplication(ArithmeticOperator *toPlace, char oper, int moveX, int moveY)
{
	int centerX, centerY, opSize;
	centerX = toPlace->get_x();
	centerY = toPlace->get_y();
	opSize = toPlace->get_size();

	if ((centerX - opSize <= 0) || (centerY - opSize <= 0) || (centerX + opSize > grid_cols) || (centerY + opSize > grid_rows))
	{
		border_error_massage(centerX, centerY, opSize, 'x', oper);
		return false;
	}
	int x = centerX - 1;
	int y = centerY - 1;
	vector<vector<OperatorCenter> > TestGrid = get_grid();
	if (TestGrid[y][x].sign != '0') {
		conflict_error_massage(centerX, centerY, opSize, 'x', oper);
		return false;
	}

	for (int i = 1; i < opSize + 1; i++) {
		if (TestGrid[y+i][x + i].sign + TestGrid[y-i][x - i].sign + TestGrid[y + i][x-i].sign + TestGrid[y - i][x+i].sign != 4 * '0') {
			conflict_error_massage(centerX, centerY, opSize, 'x', oper);
			return false;
		}
	}

	//No errors we can place.
	CenterHolder[y][x].changeValues(centerX, centerY, 'x', opSize);
	//grid[y][x] = '+';
	for (int i = 1; i < opSize + 1; i++) {
		CenterHolder[y+i][x + i].changeValues(centerX, centerY, 'x', opSize);
		CenterHolder[y-i][x - i].changeValues(centerX, centerY, 'x', opSize);
		CenterHolder[y + i][x-i].changeValues(centerX, centerY, 'x', opSize);
		CenterHolder[y - i][x+i].changeValues(centerX, centerY, 'x', opSize);
		//grid[y][x + i] = '+';
		//grid[y][x - i] = '+';
		//grid[y + i][x] = '+';
		//grid[y - i][x] = '+';
	}
	success_message(centerX, centerY, opSize, '+', oper);
	return true;
}

bool OperatorGrid::place_division(ArithmeticOperator *toPlace, char oper, int moveX, int moveY)
{
	int centerX, centerY, opSize;
	centerX = toPlace->get_x();
	centerY = toPlace->get_y();
	opSize = toPlace->get_size();

	if ((centerX - opSize <= 0) || (centerY - opSize <= 0) || (centerX + opSize > grid_cols) || (centerY + opSize > grid_rows))
	{
		border_error_massage(centerX, centerY, opSize, '/', oper);
		return false;
	}
	int x = centerX - 1;
	int y = centerY - 1;
	vector<vector<OperatorCenter> > TestGrid = get_grid();
	if (TestGrid[y][x].sign != '0') {
		conflict_error_massage(centerX, centerY, opSize, '/', oper);
		return false;
	}

	for (int i = 1; i < opSize + 1; i++) {
		if (TestGrid[y-i][x + i].sign + TestGrid[y+i][x - i].sign != 2 * '0') {
			conflict_error_massage(centerX, centerY, opSize, '/', oper);
			return false;
		}
	}

	//No errors we can place.
	CenterHolder[y][x].changeValues(centerX, centerY, '/', opSize);
	//grid[y][x] = '+';
	for (int i = 1; i < opSize + 1; i++) {
		CenterHolder[y-i][x + i].changeValues(centerX, centerY, '/', opSize);
		CenterHolder[y+i][x - i].changeValues(centerX, centerY, '/', opSize);
		//grid[y-i][x + i] = '+';
		//grid[y+i][x - i] = '+';

	}
	success_message(centerX, centerY, opSize, '/', oper);
	return true;
}

void OperatorGrid::print_operators()
{
	for (int i = 0; i < num_operators; i++) {
		operators[i]->print_operator();
	}
	return;
}


bool OperatorGrid::move_operator(int x, int y, char direction, int move_by)
{
	int centerX = CenterHolder[y - 1][x - 1].x;
	int centerY = CenterHolder[y - 1][x - 1].y;
	int size = CenterHolder[y - 1][x - 1].size;
	int newX, newY;
	char sign = CenterHolder[y - 1][x - 1].sign;



	switch (direction) {
	case'U':
		newX = centerX;
		newY = centerY - move_by;
		break;
	case'D':
		newX = centerX;
		newY = centerY + move_by;
		break;
	case'L':
		newX = centerX - move_by;
		newY = centerY;
		break;
	case'R':
		newX = centerX + move_by;
		newY = centerY;
		break;
	}
	ArithmeticOperator toPlace(newX, newY, size, sign);
	bool moved;

    vector<vector<OperatorCenter> > OldGrid = this->get_grid();
	remove_operator(this->CenterHolder, centerX, centerY);
	moved = this->place_operator(&toPlace, 'M', centerX, centerY);

	if (moved) {
		for(int i = 0; i < num_operators; i++){
			int a = operators[i]->get_x();
			int b = operators[i]->get_y();
			if (a == centerX and b == centerY) {
				operators[i]->set_x(newX);
				operators[i]->set_y(newY);
				break;
			}
		}
		return true;
	}
	this->CenterHolder = OldGrid;
	return false;
}

void remove_operator(vector<vector<OperatorCenter> >& grid, int centerX, int centerY) {
	int x = centerX - 1;
	int y = centerY - 1;
	OperatorCenter jeff = grid[y][x];

	switch (jeff.sign) {
	case '+':
		for (int i = 1; i < grid[y][x].size + 1; i++) {
			grid[y][x + i].changeValues(0, 0, '0',0 );
			grid[y][x - i].changeValues(0, 0, '0',0 );
			grid[y + i][x].changeValues(0, 0, '0',0 );
			grid[y - i][x].changeValues(0, 0, '0',0 );
		}
		break;
	case '-':
		for (int i = 1; i < grid[y][x].size + 1; i++) {
			grid[y][x + i].changeValues(0, 0, '0',0 );
			grid[y][x - i].changeValues(0, 0, '0',0 );
		}
		break;
	case 'x':
		for (int i = 1; i < grid[y][x].size + 1; i++) {
			grid[y + i][x + i].changeValues(0, 0, '0',0 );
			grid[y - i][x - i].changeValues(0, 0, '0',0 );
			grid[y + i][x - i].changeValues(0, 0, '0',0 );
			grid[y - i][x + i].changeValues(0, 0, '0',0 );
		}
		break;
	case '/':
		for (int i = 1; i < grid[y][x].size + 1; i++) {
			grid[y + i][x - i].changeValues(0, 0, '0',0 );
			grid[y - i][x + i].changeValues(0, 0, '0',0 );
		}
		break;
	}
	grid[y][x].changeValues(0, 0, '0', 0);
}
