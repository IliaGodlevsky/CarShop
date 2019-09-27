#include <iostream>
#include <fstream>
#include <algorithm>

#include "Functions.h"

unsigned input(const std::string& msg,
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

std::string input(const std::string& msg)
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

Strings load_lines(std::string filename)
{
	Strings names;
	std::string name;
	std::ifstream fin(filename);
	while (!fin.eof())
	{
		std::getline(fin, name);
		names.push_back(name);
	}
	fin.close();
	return names;
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
	static Strings names = load_lines(filename);
	std::string name = names[rand() % names.size()];
	unsigned year = linear(YEAR_ADD);
	unsigned cost = linear(COST_MULT, COST_MULT);
	unsigned power = linear(POW_ADD, POW_MULT);
	return Car(name, year, cost, power);
}

Car defined_car()
{
	return Car().input_car();
}

inline unsigned linear(unsigned b,
	unsigned a,
	unsigned x)
{
	return a * x + b;
}

void show_car(std::ostream& os,
	const Car& car,
	unsigned index)
{
	os << "     " << index << std::endl
		<< car << std::endl;
}

void show_cars(std::ostream& os,
	const Park& cars)
{
	unsigned i = 0;
	for (auto& car : cars)
		show_car(os, car, ++i);
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
			show_car(os, car, i);
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
			<< ". " << menu[i];
		if (i % 2 == 0)
			std::cout << '\t';
		if (i % 2 != 0 && i != size - 1)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}