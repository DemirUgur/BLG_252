#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class ingredient { //abstract base class
	string name;
	int type;
	int ItemCount;
	double price;
public:
	ingredient(string = "",int = 0 ,double = 0.0, int = 0 );

	virtual double calculate_cost() = 0;
	string get_name();
	int get_type();
	int get_ItemCount();
	double get_price();
	void set_name(string);
	void set_type(int);
	void set_ItemCount(int);
	void set_price(double);
	friend ostream& operator<<(ostream& os, ingredient const& tc) {
		return os << tc.name << " " << tc.type << " " << tc.ItemCount << " " << tc.price << endl;
	}
};

class type1 : public ingredient {
public:
	type1(string = "", int = 0, double = 0.0);
	double calculate_cost();
};

class type2 : public ingredient {
public:
	type2(string = "", int = 0, double = 0.0);
	double calculate_cost();
};

class type3 : public ingredient {
public:
	type3(string = "", int = 0, double = 0.0);
	double calculate_cost();
};

struct food {
	string name;
	vector<ingredient*> ingredients;
	double cost = 0;
	double calculate_cost();
};

ingredient::ingredient(string name, int ItemCount, double price, int type)
{
	//cout << "ingredient constructor" << endl;
	this->name = name;
	this->ItemCount = ItemCount;
	this->price = price;
	this->type = type;
}


string ingredient::get_name()
{
	return name;
}

int ingredient::get_type()
{
	return type;
}

int ingredient::get_ItemCount()
{
	return ItemCount;
}

double ingredient::get_price()
{
	return price;
}

void ingredient::set_name(string givenName)
{
	name = givenName;
}

void ingredient::set_type(int a)
{
	type = a;
}

void ingredient::set_ItemCount(int givenItemCount)
{
	ItemCount = givenItemCount;
}

void ingredient::set_price(double givenPrice)
{
	price = givenPrice;
}

double food::calculate_cost()
{
	double totalCost = 0;
	for (int i = 0; i < int(ingredients.size()); i++){
		totalCost += ingredients[i]->calculate_cost(); //P O L Y M O P R H I S M
	}
	return totalCost;
}

type1::type1(string name, int Itemcount, double Price)
{
	set_name(name);
	set_price(Price);
	set_type(1);
	set_ItemCount(Itemcount);
}

double type1::calculate_cost()
{
	//cout << "type 1 cost calculated: " << endl;
	double cost = 0;
	cost += get_ItemCount() * get_price();
	return cost;
}

type2::type2(string name, int Itemcount, double Price)
{
	set_name(name);
	set_price(Price);
	set_type(2);
	set_ItemCount(Itemcount);
}

type3::type3(string name, int Itemcount, double Price)
{
	set_name(name);
	set_price(Price);
	set_type(3);
	set_ItemCount(Itemcount);
}

double type2::calculate_cost()
{
	//cout << "type 2 cost calculated: " << endl;
	double cost = 0;
	cost += get_ItemCount() * get_price();
	return cost;
}

double type3::calculate_cost()
{
	//cout << "type 3 cost calculated: " << endl;
	double cost = 0;
	cost += get_ItemCount() * get_price();
	return cost;
}

double findPrice(vector<ingredient*>& stock, string name);
void ServeOrder(vector<ingredient*>& , const vector<food>&);

void readMenu(vector<food>& menu, vector<ingredient*>& Stock) {
	type1* a;
	type2* b;
	type3* c;
	ifstream fptr;
	fptr.open("menu.txt");
	string foodName, line, untilComma;
	getline(fptr, foodName);
	int i = 0;
	while (getline(fptr, line)) {
		//within this while loop a new food is created to be added to the 
		stringstream ss;
		ss << line;
		getline(ss, foodName, '\t');
		food newFood;
		newFood.name = foodName; //Name of the food.
		while (getline(ss, untilComma, ',')) {
			if (untilComma == "N/A") {
				double price = findPrice(Stock, foodName);
				b = new type2(foodName, 1, price);
				newFood.ingredients.push_back(b);
				newFood.cost = newFood.calculate_cost();
				break;
			}
			//in this loop the ingredient vector of the new food is filled with the given ingredients.
			stringstream comma;
			string weight, name;
			int itemCount;
			comma << untilComma;
			//if we have a type 2 element the name will be empty and weight will be used as name.
			comma >> itemCount;
			comma >> weight;
			if (weight == "gram") {
				comma.get();
				getline(comma, name, ',');
				double price = findPrice(Stock, name);
				a = new type1(name, itemCount,price);
				newFood.ingredients.push_back(a);
			}
			else if (weight == "ml") {
				comma.get();
				getline(comma, name, ',');
				double price = findPrice(Stock, name);
				c = new type3(name, itemCount, price);
				newFood.ingredients.push_back(c);
			}
			else {
				comma.get();
				getline(comma, name, ',');
				weight = weight + name;
				double price = findPrice(Stock, weight);
				b = new type2(weight, itemCount, price);
				newFood.ingredients.push_back(b);
			}
			newFood.cost = newFood.calculate_cost(); //polymorhisim used in calculate_cost()
		}
		menu.push_back(newFood);
	}
}

double findPrice(vector<ingredient*>& stock, string name) {
	for (int i = 0; i < int(stock.size()); i++) {
		if (stock[i]->get_name() == name) {
			return stock[i]->get_price();
		}
	}
	return -1;
}


int main() {
	vector<ingredient*> Stock;
	
	ifstream fptr;
	fptr.open("stock.txt");
	string line;
	getline(fptr, line);
	int i = 0;
	type1* a;
	type2* b;
	type3* c;

	while (getline(fptr, line)) {
		if (line == "") {
			continue;
		}
		string name;
		int type, itemCount;
		double price;
		stringstream ss;
		ss << line;
		getline(ss, name, '\t');
		ss >> type >> itemCount >> price;
		if (type == 1) {
			a = new type1(name, itemCount, price);
			Stock.push_back(a);
		}
		else if (type == 2) {
			b = new type2(name, itemCount, price);
			Stock.push_back(b);
		}
		else if (type == 3) {
			c = new type3(name, itemCount, price);
			Stock.push_back(c);
		}
		//Stock read.
	}
	vector<food> menu;
	readMenu(menu, Stock); //reads menu
	ServeOrder(Stock, menu); //reads orders and does operations necessary
	return 0;
}

bool stockController(int a, string name ,vector<ingredient*>& Stock, int amount, string foodName) {
	int i = 0;
	while (Stock[i]->get_name() != name && i < Stock.size()) {
		i++;
	}
	if (Stock[i]->get_ItemCount() < a * amount || i >= Stock.size()) {
		throw "We don't have enough " + foodName;
		//cout << "We don't have enough " << name;
		return false;
	}
	else {
		int newItemCount = Stock[i]->get_ItemCount() - a * amount;
		Stock[i]->set_ItemCount(newItemCount);
		return true;
	}
}

bool toCheck(const food& toCheck, vector<ingredient*>& Stock, int amount) {
	//ingredients of the food are affordable by the Stock.
	bool affordable = false;
	
	for (unsigned int i = 0; i < toCheck.ingredients.size(); i++) {
		try{
			affordable = stockController(toCheck.ingredients[i]->get_ItemCount(), toCheck.ingredients[i]->get_name(), Stock, amount, toCheck.name);
		}
		catch (string result) {
			cout << result << endl;
			break;
		}
	}
	return affordable;
}

void ServeOrder(vector<ingredient*>& Stock, const vector<food>& menu) {
	ifstream fptr;
	fptr.open("order.txt");
	string tableNumber;
	int dishNumber;
	double totalCost;
	while (fptr >> tableNumber >> dishNumber) {
		totalCost = 0;
		cout << tableNumber << " ordered: " << endl;
		for (int i = 0; i < dishNumber; i++) {

			int amount;
			string dishName;
			fptr >> amount;
			fptr.get();
			getline(fptr, dishName);
			int j = 0;
			while (menu[j].name != dishName) {
				j++;
			}
			bool served;
			served = toCheck(menu[j], Stock, amount);
			if (served) {
				cout << amount << " " << dishName << " cost: " << menu[j].cost * amount << endl;
				totalCost += menu[j].cost * amount;
			}
		}
		double tip = totalCost * 15 / 100;
		double tax = totalCost * 8 / 100;
		double price = totalCost + tip + tax;

		printf("Tip is %0.2lf\n", tip);
		printf("Total Cost: %0.2lf\n", price);
		printf("*************************\n");
	}
	fptr.close();
}

void writeStockToFile(const vector<ingredient*>& Stock)
{
	ofstream fptr;
	fptr.open("stock.txt");
	fptr << "Name	Type	ItemCount	Price\n";
	for (int i = 0; i < Stock.size(); i++) {
		if (Stock[i]->get_ItemCount() != 0) {
			fptr << Stock[i]->get_name() << "\t" << Stock[i]->get_type() << "\t" << Stock[i]->get_ItemCount() << "\t" << Stock[i]->get_price() << "\n";
		}
	}
	fptr.close();
}