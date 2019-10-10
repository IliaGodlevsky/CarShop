#include <algorithm>

#include "Functions.h"

Car rand_car()
{
	static Strings names = load_file(car_names);
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

Plant plant()
{
	enum { RAND = 1, DEFINED };
	const unsigned GENERATORS = 2;
	Plant generators[GENERATORS]
	{ rand_car,defined_car };
	const char* gen_menu[GENERATORS] 
		= { "Random","Defined" };
	menu(gen_menu, GENERATORS);
	unsigned plant = input(add_msg, 
		DEFINED, RAND);
	return generators[plant - 1];
}

inline unsigned linear(unsigned b,
	unsigned a,
	unsigned x)
{
	return a * x + b;
}

Strings load_file(std::string filename)
{
	std::ifstream fin;
	file_opening(fin, filename);
	return file_reading(fin);
}

Strings file_reading(std::ifstream& is)
{
	Strings names;
	std::string name;
	while (!is.eof())
	{
		std::getline(is, name);
		names.push_back(name);
	}
	is.close();
	return names;
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

void menu(const char* const menu[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << i + 1
			<< ". " << menu[i];
		if (!fmod(i, 2))
			std::cout << '\t';
		if (fmod(i, 2) && i != size - 1)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

void wait(clock_t seconds)
{
	clock_t start = clock();
	while (clock() - start <
		seconds * CLOCKS_PER_SEC)
		continue;
	system(CMNDS, pause, cls);
}

void system(size_t cmnds,
	const char* first...)
{
	const char** pointer = &first;
	for (size_t i = 0; i < cmnds; i++)
		system(*(pointer + i));
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