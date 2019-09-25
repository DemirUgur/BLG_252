#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using  namespace std;



struct OperatorCenter {
	char sign ;
	int x ;
	int y ;
	int size;
	OperatorCenter(){
        sign = '0';
        x = 0;
        y = 0;
        size = 0;
	}
	void changeValues(int Givenx, int Giveny,char Givensign ,int Givensize) {
		sign = Givensign;
		x = Givenx;
		y = Giveny;
		size = Givensize;
	}
};

class Operator {
	int center_x;
	int center_y;
	int op_size;

public:
	Operator(int x = 0, int y = 0, int size = 0);

	void reset(int new_x, int new_y, int new_size);

	void set_x(int new_x);
	int get_x();

	void set_y(int new_y);
	int get_y();

	void set_size(int new_size);
	int get_size();
};

class ArithmeticOperator : public Operator {
	char sign;
public:
	ArithmeticOperator(int x, int y, int size, char sign);
	char get_sign() { return sign; }
	void print_operator();
};

class OperatorGrid {
	int grid_rows;
	int grid_cols;
	char **grid;
	vector <vector<OperatorCenter> > CenterHolder;
	int num_operators;
	ArithmeticOperator *operators[200];

public:
	OperatorGrid(int rows = 0, int cols = 0);
	~OperatorGrid();

	vector<vector<OperatorCenter> > get_grid();

	bool place_operator(ArithmeticOperator*, char = 'P', int = 0, int = 0 );
	bool move_operator(int x, int y, char direction, int move_by);
	void print_operators();
	bool place_plus(ArithmeticOperator*, char = 'P', int = 0, int = 0);
	bool place_minus(ArithmeticOperator*, char = 'P', int = 0, int = 0);
	bool place_multiplication(ArithmeticOperator*, char = 'P', int = 0, int = 0);
	bool place_division(ArithmeticOperator*, char = 'P', int = 0, int = 0);
};

#endif
