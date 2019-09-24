#include <iostream>
#include <fstream>
#include <algorithm>

#include "Functions.h"
#include "Constants.h"

unsigned input(const char* msg,
	unsigned up, unsigned down)
{
	unsigned choice;
	std::cout << msg;
	std::cin >> choice;
	while (error(choice, up, down))
	{
		eatline(std::cin);
		std::cout << msg;
		std::cin >> choice;
	}
	eatline(std::cin);
	return choice;
}

std::string input(const char* msg)
{
	std::string choice;
	std::cout << msg;
	std::getline(std::cin, choice);
	while (std::cin.fail())
	{
		eatline(std::cin);
		std::cout << msg;
		std::getline(std::cin, choice);
	}
	return choice;
}

bool error(unsigned choice,
	unsigned up, unsigned down)
{
	return std::cin.fail() ||
		choice > up || choice < down;
}

void eatline(std::istream& is)
{
	is.clear();
	while (!iscntrl(is.get()))
		continue;
}

void pause(clock_t seconds)
{
	clock_t start = clock();
	while (clock() - start <
		seconds * CLOCKS_PER_SEC)
		continue;
	system("pause");
	system("cls");
}

Car rand_car()
{
	static Names names = load_names();
	std::string name = names[rand() % names.size()];
	unsigned year = linear(YEAR_ADD);
	unsigned cost = linear(COST_MULT, COST_MULT);
	unsigned power = linear(POW_ADD, POW_MULT);
	return Car(name, year, cost, power);
}

Car defined_car()
{
	Car temp;
	temp.input_car();
	return temp;
}

inline unsigned linear(unsigned b,
	unsigned a, unsigned x)
{
	return a * x + b;
}

void show_cars(std::ostream& os,
	const Park& cars)
{
	unsigned i = 0;
	for (auto& car : cars)
		os << "     " << ++i << std::endl
		<< car << std::endl;
}

bool show_cars(std::ostream&os,
	const Park& cars,
	const Seller& seller)
{
	unsigned i = 1;
	unsigned count = 0;
	for (auto& car : cars)
	{
		if (seller(car))
		{
			os << "     " << i << std::endl;
			os << car << std::endl;
			count++;
		}
		i++;
	}
	return count;
}

void menu(const char* const menu[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << i + 1
			<< "." << menu[i];
		if (i % 2 == 0)
			std::cout << '\t';
		if (i % 2 != 0 && i != size - 1)
			std::cout << '\n';
		if (i == size - 1)
			std::cout << std::endl;
	}
}

void visit_auto_shop(AutoShop& shop)
{
	while (!shop.customer_is_out())
	{
		shop.take_request();
		shop.fulfill_request();
	}
	shop.propose_catalog();
}

Names load_names()
{
	std::string name;
	Names names;
	std::ifstream fin(filename);
	while (!fin.eof())
	{
		std::getline(fin, name);
		while (fin.fail())
		{
			eatline(fin);
			std::getline(fin, name);
			if (fin.eof())
				break;
		}
		names.push_back(name);
	}
	fin.close();
	return names;
}