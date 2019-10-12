#include <algorithm>
#include <fstream>

#include "Functions.h"
#include "Constants.h"
#include "Functor.h"
#include "View.h"

///// CLASS CAR METHODS DEFINITIONS /////

Car::Car() : name("Car"), year(MIN_YEAR),
cost(MIN_COST), power(MIN_POWER) {}

Car::Car(const std::string& name, unsigned year,
	unsigned cost, unsigned power) :
	name(name), year(year),
	cost(cost), power(power) {}

std::ostream& operator <<(std::ostream& os, const Car& car)
{
	os << "Name: " << car.name << std::endl;
	os << "Year: " << car.year << std::endl;
	os << "Cost: " << car.cost << " $\n";
	os << "Power: " << car.power << " hp\n";
	return os;
}

Car& Car::input_car()
{
	name = input(name_msg);
	year = input(year_msg, 
		MAX_YEAR, MIN_YEAR);
	power = input(power_msg, 
		MAX_POWER, MIN_POWER);
	cost = input(cost_msg, 
		MAX_COST, MIN_COST);
	return *this;
}

bool Car::operator==(const Car& first)const
{
	return
		name == first.name &&
		year == first.year &&
		cost == first.cost &&
		power == first.power;
}

///// CLASS AUTOSHOP METHODS DEFINITIONS /////

AutoShop::AutoShop(size_t size, Plant car_gen)
	: request(FIND), cars(size)
{
	std::generate(cars.begin(),
		cars.end(), car_gen);
}

void AutoShop::stock()
{
	cars.push_back(plant()());
}

void AutoShop::sell()
{
	if (!cars.empty())
	{
		View view;
		view.show_options();
		view.show_cars(std::cout, cars);
		unsigned to_sell = input(sell_msg,
			cars.size(), 1U) - 1U;
		cars.erase(cars.begin() + to_sell);
	}
	else std::cout << empty_msg;
}

void AutoShop::take_request()
{
	menu(shop_menu, SHOP_MENU_SIZE);
	request = (Char)input(request_msg,
		FIND, QUIT);
	if (request > QUIT) system(cls);
}

void AutoShop::fulfill_request()
{
	switch (request)
	{
	case STOCK: stock(); break;
	case SELL:  sell();	 break;
	case SHOW:  show();	 break;
	case SORT:  sort();	 break;
	case FIND:  find();	 break;
	}
	wait();
}

void AutoShop::sort()
{
	Comparator compare;
	compare.choose_options();
	std::sort(cars.begin(),
		cars.end(), compare);
}

void AutoShop::show()const
{
	View view;
	view.show_options();
	view.show_cars(std::cout, cars);
}

void AutoShop::find()const
{
	Finder finder;
	View view((bool)NAME, bool(COST),
		bool(YEAR), bool(POWER), bool(EQUAL));
	if (!view.show_cars(std::cout, cars, finder))
		std::cout << not_found;
}

void AutoShop::propose_catalog()const
{
	const bool answer =
		input(calalog_answer, YES, NO);
	if (YES == answer)
	{
		View view;
		view.show_options();
		std::ofstream fout;
		file_opening(fout, catalog);
		view.show_cars(fout, cars);
		std::cout << catalog_msg
			<< catalog << std::endl;
		fout.close();
	}
	wait();
}

bool AutoShop::customer_is_out()const
{
	return request == QUIT;
}