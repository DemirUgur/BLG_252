#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
#include "Polynomial.h"



Polynomial::Polynomial(const Polynomial& object_in) {
	degree = object_in.degree;
	coeff = new int[degree + 1];
	for (int i = 0; i < degree + 1; i++) {
		coeff[i] = object_in.coeff[i];
	}
}

Polynomial::~Polynomial() {
	delete[] coeff;
}

ostream& operator<<(ostream& os, Polynomial& c) {
	const int PolyDegree = c.get_degree();
	const int* PolyCoeff = c.get_coeff();

	int i = PolyDegree;
	for (i; i > 1; i--) {
		if ((PolyCoeff[PolyDegree - i] != 1) && (PolyCoeff[PolyDegree - i] != 0)) {
			cout << PolyCoeff[PolyDegree - i] << "x^" << i << " + ";
		}
		else if (PolyCoeff[PolyDegree - i] == 1) {
			cout << "x^" << i << " + ";
		}
	}
	if (PolyCoeff[1] != 1 && PolyCoeff[1] != 0) {
		cout << PolyCoeff[PolyDegree - 1] << "x + ";
	}
	else if (PolyCoeff[1] == 1) {
		cout << "x + ";
	}
	if (PolyCoeff[0] != 0) {
		cout << PolyCoeff[PolyDegree];
	}
	return os;
}

Polynomial Polynomial::operator*(const Polynomial& z)const { //Poly multiplication
	int FinalDegree = this->degree + z.degree; //degree of our new poly will be the sum of participants
	int *firstCoeffs = new int[this->degree + 1];
	int *secondCoeffs = new int[z.degree + 1];
	for (int i = 0; i < this->degree + 1; i++) {
		firstCoeffs[i] = this->coeff[this->degree - i];
	}
	for (int i = 0; i < z.degree + 1; i++) {
		secondCoeffs[i] = z.coeff[z.degree - i];
	}
	int NewCoeff, newDegree;
	vector<int> hold(FinalDegree + 1, 0);
	for (int k = 0; k < this->degree + 1; k++) { //calculates the new coeffs and new degrees places them into a placeholder array
		for (int j = 0; j < z.degree + 1; j++) {
			NewCoeff = firstCoeffs[k] * secondCoeffs[j];
			newDegree = k + j;
			hold[newDegree] += NewCoeff;
		}
	}

	int *jeff = new int[FinalDegree + 1];

	for (int i = 0; i < FinalDegree + 1; i++) {
		jeff[i] = hold.back();
		hold.pop_back();
	}
	delete[] firstCoeffs;
	delete[] secondCoeffs;
	return Polynomial(FinalDegree, jeff);
}

Polynomial Polynomial::operator+(const Polynomial& z)const { //Poly addition
	int newDegree;
	int *newCoeff, *bigBoy, *smallBoy;
	if (this->degree >= z.degree) {
		newDegree = this->degree;
		bigBoy = this->coeff;
		smallBoy = z.coeff;
	}
	else {
		newDegree = z.degree;
		bigBoy = z.coeff;
		smallBoy = this->coeff;
	}
	int i = 0;
	int jeff = abs(this->degree - z.degree);
	newCoeff = new int[newDegree + 1];
	for (i; i < jeff; i++) {
		newCoeff[i] = bigBoy[i];
	}
	for (i; i < newDegree + 1; i++) {
		newCoeff[i] = bigBoy[i] + smallBoy[i - jeff];
	}
	return Polynomial(newDegree, newCoeff);
}

Polynomial::Polynomial(int Newdegree, int *Newcoeff) {
	degree = Newdegree;
	coeff = new int[degree + 1];
	for (int i = 0; i < Newdegree + 1; i++) {
		coeff[i] = Newcoeff[i];
	}
}
