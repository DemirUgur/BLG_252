#pragma once


class Polynomial {
	int *coeff;
	int degree;
public:
	//constant getters
	int get_degree() const { return degree; }
	int* get_coeff() const { return coeff; } 

	//normal getters
	int get_degree() { return degree; }
	int* get_coeff() { return coeff; }

	Polynomial(int,int*);
	Polynomial(const Polynomial&); //copy constructor
	~Polynomial();
	
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator*(const Polynomial&) const;
	friend ostream& operator<<(ostream& os, Polynomial&);
};
