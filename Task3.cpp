#include<cstdlib>
#include<cstring>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Polynom
{
    int deg;
    int coef;
	Polynom* next;
};

typedef Polynom* Pointer;

Pointer polynom = new Polynom();

void print(Pointer polynom, bool recursive = false) {
	if (polynom->coef == 0 && (!recursive || polynom->next != nullptr)) {
		print(polynom->next, true);
		return;
	}
	if (recursive && (polynom->deg > 0)) {
		std::cout << "+";
	}
	if (polynom->deg == 0 || polynom->coef != 1) {
		std::cout << polynom->coef;
	}
	if (polynom->deg != 0) {
		std::cout << "x";
	}
	if (polynom->deg != 1 && polynom->deg != 0) {
		std::cout << "^" << polynom->deg;
	}
	if (polynom->next != nullptr)
		print(polynom->next, true);
		else
		std::cout << std::endl;
}

int getDegree(Pointer polynom) {
	Pointer cur = polynom;
	int max = -1;
	while (cur != nullptr) {
		if (max < cur->deg) max = cur->deg;
		cur = cur->next;
	}
	return max;
}

void removeDuplicates(Pointer& polynom) {
	int max = getDegree(polynom);
	Pointer res = new Polynom();
	Pointer node = res;

	for (int i = 0; i <= max; i++) {
		int coef = 0;
		Pointer cur = polynom;
		while (cur != nullptr) {
			if (cur->deg == i) coef += cur->coef;
			cur = cur->next;
		}
		node->coef = coef;
		node->deg = i;
		if (i != max) {
			node->next = new Polynom();
			node = node->next;
		}
	}

	node->next = nullptr;

	polynom = res;
}

void input()
{
	std::string pol;
    cout << "vvedite polynom: ";
	getline(cin, pol);

	remove_if(pol.begin(), pol.end(), isspace);

	if (empty(pol)) return;

	if (pol[0] != '-') pol = "+" + pol;

	int ind = 0;
	int current = 0;
	char symbol = ' ';
	bool isDegree = false;
	bool isNumber = true;
	bool isNegative = false;
	bool hasCoefficient = false;
	int degree = 0;
	Pointer node = polynom;

	while (ind < pol.length()) {
		symbol = pol[ind];
		if (isdigit(symbol)) {
			if (isDegree) {
				degree = degree * 10 + symbol - 48;
			}
			else {
				hasCoefficient = true;
				current = current * 10 + symbol - 48;
			}
		}
		if (symbol == 'x') {
			isNumber = false;
		}
		if (symbol == '^') {
			isDegree = true;
		}
		if (symbol == '+' || symbol == '-' || ind == pol.length() - 1) {
			if ((!isNumber) && (degree == 0)) degree = 1;
			if (!hasCoefficient) current = 1;
			if (isNegative) current *= -1;

			node->coef = current;
			node->deg = degree;

			if (ind != pol.length() - 1) {
				node->next = new Polynom();
				node = node->next;
			}

			hasCoefficient = false;
			isNumber = true;
			isDegree = false;
			current = 0;
			degree = 0;
			isNegative = symbol == '-';
		}
		ind++;
	}

	node->next = nullptr;

	polynom = polynom->next;

	removeDuplicates(polynom);

	print(polynom);
}

int main()
{
    input();
    cout << "\nPolynom: ";
}