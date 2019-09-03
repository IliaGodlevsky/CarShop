#include <iostream>

#include "Functions.h"
#include "Constants.h"

namespace shop
{
	int input(const char* msg,
		int up, int down)
	{
		int choice;
		std::cout << msg;
		std::cin >> choice;
		while (err(choice, up, down))
		{
			eatline();
			std::cout << msg;
			std::cin >> choice;
		}
		eatline();
		return int(choice);
	}

	void eatline()
	{
		std::cin.clear();
		while (!iscntrl(std::cin.get()))
			continue;
	}

	bool err(int choice,
		int up, int down)
	{
		return std::cin.fail() ||
			choice > up || choice < down;
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

	shop::Car rand_car()
	{
		std::string name = names[rand() % TYPES];
		unsigned year = years[rand() % TYPES];
		unsigned cost = costs[rand() % TYPES];
		unsigned power = powers[rand() % TYPES];
		return shop::Car(name, year, cost, power);
	}

	shop::Car defined_car()
	{
		shop::Car temp;
		std::cin >> temp;
		return temp;
	}

	void show_cars(std::ostream& os,
		const Park& cars)
	{
		unsigned i = 0;
		for (auto& car : cars)
		{
			os << "     " << ++i << std::endl
				<< car << std::endl;
		}
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
}