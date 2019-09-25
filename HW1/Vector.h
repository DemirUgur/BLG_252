#pragma once


class MyVector {
	int degree;
	int *coeff;
public:
	//constant getters
	int get_degree() const { return degree; }
	int* get_coeff() const { return coeff; }

	//normal getters
	int get_degree()  { return degree; }
	int* get_coeff()  { return coeff; }
	MyVector(int, int*);
	MyVector(const MyVector&);
	~MyVector();
	
	const MyVector& operator=(const MyVector&);
	MyVector operator+(const MyVector& c)const;
	MyVector operator*(const int& c)const;
	int operator*(const MyVector& c)const;
	friend ostream& operator<<(ostream& os, const MyVector& c);
};

