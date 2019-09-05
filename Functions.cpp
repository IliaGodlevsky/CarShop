#include <iostream>

#include "Functions.h"
#include "Constants.h"

namespace shop
{
	unsigned input(const char* msg,
		unsigned up, unsigned down)
	{
		unsigned choice;
		std::cout << msg;
		std::cin >> choice;
		while (error(choice, up, down))
		{
			eatline();
			std::cout << msg;
			std::cin >> choice;
		}
		eatline();
		return choice;
	}

	std::string input(const char* msg)
	{
		std::string choice;
		std::cout << msg;
		std::getline(std::cin, choice);
		while (std::cin.fail())
		{
			eatline();
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

	void eatline()
	{
		std::cin.clear();
		while (!iscntrl(std::cin.get()))
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

	shop::Car rand_car()
	{
		std::string name = names[rand() % TYPES];
		unsigned year = rand() % TYPES + 1;
		unsigned cost = rand() % TYPES + 1;
		unsigned power = powers[rand() % TYPES];
		return shop::Car(name, year + YEAR_ADD, 
			cost * COST_MULTI, power);
	}

	shop::Car defined_car()
	{
		shop::Car temp;
		temp.input_car();
		return temp;
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
		const Park& cars, const Seller& seller)
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
}