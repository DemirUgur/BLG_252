#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
#include "Vector.h"



const MyVector& MyVector::operator=(const MyVector& object_in) {
	if (degree != object_in.degree) {
		degree = object_in.degree;
		delete[] coeff;
		coeff = new int[degree + 1];
	}
	for (int i = 0; i < this->degree + 1; i++) {
		this->coeff[i] = object_in.coeff[i];
	}
	return *this;
}
MyVector::MyVector(const MyVector& object_in) {
	this->degree = object_in.degree;
	coeff = new int[this->degree];
	for (int i = 0; i < this->degree + 1; i++) {
		this->coeff[i] = object_in.coeff[i];
	}
}

MyVector::~MyVector() {
	delete[] coeff;
}

MyVector MyVector::operator+(const MyVector& c) const { //vector addition
	if (c.degree != this->degree) {
		cout << "Non Compatible Vector addition!" << endl;
		MyVector emptyVector(0, 0);
		return emptyVector;
	}
	int *newCoeff = new int[this->degree + 1];
	for (int i = 0; i < this->degree + 1; i++) {
		newCoeff[i] = this->coeff[i] + c.coeff[i];
	}
	return MyVector(degree, newCoeff);
}

int MyVector::operator*(const MyVector& c) const { //vector multiplication
	if (c.degree != this->degree) {
		cout << "Non Compatible with dot Product!" << endl;
		return 0;
	}
	int sum = 0;
	for (int i = 0; i < this->degree; i++) {
		sum += this->coeff[i] * c.coeff[i];
	}
	return sum;
}

MyVector MyVector::operator*(const int& c) const { //vector dot product
	int *newCoeff = new int[this->degree + 1];
	for (int i = 0; i < this->degree + 1; i++) {
		newCoeff[i] = this->coeff[i] * c;
	}
	return MyVector(degree, newCoeff);
}

MyVector::MyVector(int size, int *values) {
	degree = size;
	coeff = new int[degree + 1];
	for (int i = 0; i < size + 1; i++) {
		coeff[i] = values[i];
	}
}

ostream& operator<<(ostream& os, const MyVector& c) {
	const int VectorDegree = c.get_degree();
	const int* VectorCoeff = c.get_coeff();
	cout << "(" << VectorCoeff[0];
	for (int i = 1; i < VectorDegree; i++) {
		cout << ", " << VectorCoeff[i];
	}
	cout << ")";
	return os;
}