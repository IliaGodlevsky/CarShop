#include <algorithm>
#include <iomanip>

#include "Functions.h"

Car rand_car()
{
	static Strings names = load_file(car_names);
	std::string name = names[random(names.size() - 1)];;
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
	unsigned plant = input(gen_msg, 
		DEFINED, RAND);
	return generators[plant - 1];
}

unsigned random(unsigned max,
	unsigned min)
{
	std::random_device seed;
	std::mt19937 eng(seed());
	// [min, max]
	return Random(min, max)(eng);
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
		while (!is && !is.eof())
			std::getline(eatline(is), name);
		names.push_back(name);
	}
	is.close();
	return names;
}

void show_car(std::ostream& os,
	const Car& car,
	unsigned index)
{
	const unsigned INDENT
		= unsigned(std::log10(index));
	os << index << std::setw(SPACE_NUM_NAME - INDENT)
		<< car << std::endl;
}

void show_cars(std::ostream& os,
	const Park& cars)
{
	table_head(os);
	unsigned i = 0;
	for (auto& car : cars)
		show_car(os, car, ++i);
}

bool show_cars(std::ostream&os,
	const Park& cars,
	const Seller& seller)
{
	table_head(os);
	unsigned i = 0;
	unsigned count = 0;
	for (auto& car : cars)
	{
		i++;
		if (seller(car))
		{
			show_car(os, car, i);
			count++;
		}
	}
	return count;
}

void table_head(std::ostream& os)
{
	os << "#" << std::setw(SPACE_NUM_NAME) << "Name"
		<< std::setw(SPACE_NAME_COST * 2) 
		<< "Cost\tYear\tPower\n";
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

std::istream& eatline(std::istream& is)
{
	is.clear();
	while (!iscntrl(is.get()))
		continue;
	return is;
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
	const char** command = &first;
	for (size_t i = 0; i < cmnds; i++)
		system(*(command + i));
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