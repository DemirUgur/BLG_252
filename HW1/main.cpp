#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
#include "Vector.h"
#include "Polynomial.h"

void ReadFromFile(vector<Polynomial>&, vector<MyVector>&);
void printMenu();
void printList(vector<Polynomial>&, vector<MyVector>&);
void PolynomialOperation(vector<Polynomial>&);
void VectorOperation(vector<MyVector>&);

int main() {
	vector <Polynomial> Pollies;
	vector <MyVector> Vectors;
	ReadFromFile(Pollies, Vectors);
	int choice = 4;
	do {
		if (choice == 4) {
			printMenu();
		}
		do {
			cout << "Enter an option(4 for help): ";
			cin >> choice;
		} while (choice > 4 || choice < 0);
		switch (choice) {
		case 0:
			return 0;
		case 1:
			printList(Pollies, Vectors);
			break;
		case 2:
			PolynomialOperation(Pollies);
			break;
		case 3:
			VectorOperation(Vectors);
			break;
		default:
			break;
		}
	} while (choice != 0);
}

void VectorOperation(vector<MyVector>& vectors) {
	cout << "Which vector operation would you like to do?(+:addition, *:Scalar Multiplication, .:dot products):" << endl;
	int a, b;
	char c;
	cin >> a >> c >> b;
	if (c == '*') {
		MyVector jeff = vectors[a - 1] * b;
		cout << vectors[a - 1];
		cout << " " << c << " " << b << " = ";
		cout << jeff;
		cout << endl;
	return;
	}
	cout << vectors[a - 1];
	cout << " " <<  c << " ";
	cout << vectors[b - 1];
	cout << " = ";
	if(c == '+'){
		MyVector jeff = vectors[a - 1] + vectors[b - 1];
		cout << jeff;
		cout << endl;
		return;
	}
	else if(c == '.'){
		int dotProduct = vectors[a - 1] * vectors[b-1];
		cout << dotProduct;
		cout << endl;
		return;
	}

}

void PolynomialOperation(vector<Polynomial>& Pollies){
	cout << "Which polynomial operation would you like to do?(+:addition, *:multiplication):" << endl;
	int a, b;
	char c;
	cin >> a >> c >> b;
	cout << "(";
	cout << Pollies[a-1];
	cout << ") " << c << " (";
	cout << Pollies[b-1];
	cout << ") = " ;
	if (c == '+'){
		Polynomial jeff = Pollies[a-1] + Pollies[b-1];
		cout << jeff;
		cout << endl;
		return;
	}else if(c == '*'){
		Polynomial jeff = Pollies[a - 1] * Pollies[b - 1];
		cout << jeff;
		cout << endl;
		return;
	}
}

void printList(vector<Polynomial>& pollies, vector<MyVector>& vectors) {
	cout << "Vectors:" << endl;
	for (unsigned int i = 0; i < vectors.size(); i++) {
		printf("%d. ", i + 1);
		cout << vectors[i];
		cout << endl;
	}
	cout << "Polynomials: " << endl;
	for (unsigned int i = 0; i < pollies.size(); i++) {
		printf("%d. ", i + 1);
		cout << pollies[i];
		cout << endl;
	}

}

void printMenu() {
	cout << "Polynomial and Vector List Program!" << endl;
	cout << "Polynomials and Vectors are read from the text files!" << endl;
	cout << "Possible Actions:" << endl;
	cout << "1.Print Polynomial and Vector lists" << endl;
	cout << "2.Do a polynomial operation" << endl;
	cout << "3.Do a vector operation" << endl;
	cout << "0. Exit the program" << endl;

}
//reads from the file into the Polynomial and vector std::vector s
void ReadFromFile(vector<Polynomial>& Pollies, vector<MyVector>& Vectors){
	ifstream fin1, fin2;
	fin1.open("Polynomial.txt");
	int PolyNumber, degree;
	int *coeff;
	fin1 >> PolyNumber;
	for (int i = 0; i < PolyNumber; i++) {
		fin1 >> degree;
		coeff = new int[degree + 1];
		for (int k = 0; k < degree + 1; k++) {
			fin1 >> coeff[k];
		}

		Polynomial newPolly(degree, coeff);

		Pollies.push_back(newPolly);
		delete[] coeff;
	}
	fin1.close();

	fin2.open("Vector.txt");
	int VectorNumber, degree2;
	int *coeff2;
	fin2 >> VectorNumber;
	for (int i = 0; i < VectorNumber; i++) {
		fin2 >> degree2;
		coeff2 = new int[degree2];
		for (int k = 0; k < degree2; k++) {
			fin2 >> coeff2[k];
		}
		MyVector newVector(degree2, coeff2);
		Vectors.push_back(newVector);
		delete[] coeff2;
	}
	fin2.close();
}
