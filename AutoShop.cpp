#include <algorithm>
#include <fstream>

#include "Functions.h"
#include "Constants.h"


///// CLASS CAR METHODS DEFINITIONS /////

Strings message = load_lines(messages);

Car::Car() : name("Car"), year(1900),
cost(0), power(1) {}

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
	name = input(message[NAME_MSG]);
	year = input(message[YEAR_MSG], MAX_YEAR, MIN_YEAR);
	power = input(message[POWER_MSG], MAX_POWER, MIN_POWER);
	cost = input(message[COST_MSG], MAX_COST, MIN_COST);
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

///// CLASS SELLER METHODS DEFINITIONS /////

Seller::Seller()
{
	compare[0] = &Seller::is_less_name;
	compare[1] = &Seller::is_less_cost;
	compare[2] = &Seller::is_greater_year;
	compare[3] = &Seller::is_greater_power;
	find[0] = &Seller::have_same_name;
	find[1] = &Seller::have_same_cost;
	find[2] = &Seller::have_same_year;
	find[3] = &Seller::have_same_power;
	find[4] = &Seller::are_same;
}
bool Seller::operator()(const Car& first, const Car& second)const
{
	return (this->*compare[to_compare - 1])(first, second);
}

bool Seller::is_less_name(const Car& first, const Car& second)const
{
	return first.name < second.name;
}

bool Seller::is_less_cost(const Car& first, const Car& second)const
{
	return first.cost < second.cost;
}

bool Seller::is_greater_year(const Car& first, const Car& second)const
{
	return first.year > second.year;
}

bool Seller::is_greater_power(const Car& first, const Car& second)const
{
	return first.power > second.power;
}

bool Seller::operator()(const Car& first)const
{
	return (this->*find[to_find - 1])(first, car_to_search);
}

bool Seller::are_same(const Car& first, const Car& second)const
{
	return first == second;
}

bool Seller::have_same_name(const Car& first, const Car& second)const
{
	return first.name == second.name;
}

bool Seller::have_same_cost(const Car& first, const Car& second)const
{
	return first.cost == second.cost;
}

bool Seller::have_same_year(const Car& first, const Car& second)const
{
	return first.year == second.year;
}

bool Seller::have_same_power(const Car& first, const Car& second)const
{
	return first.power == second.power;
}

void Seller::choose_sort_options()
{
	menu(seller_menu, SORT_OPTIONS);
	to_compare = input(message[SORT_MSG],
		POWER, NAME);
}

void Seller::choose_find_option()
{
	menu(seller_menu, FIND_OPTIONS);
	to_find = input(message[FIND_MSG], EQUAL, NAME);
}

void Seller::search_request()
{
	switch (to_find)
	{
	case NAME:
		car_to_search.name = input(message[NAME_MSG]); break;
	case YEAR:
		car_to_search.year = input(message[YEAR_MSG],
			MAX_YEAR, MIN_YEAR); break;
	case COST:
		car_to_search.cost = input(message[COST_MSG],
			MAX_COST, MIN_COST); break;
	case POWER:
		car_to_search.power = input(message[POWER_MSG],
			MAX_POWER, MIN_POWER); break;
	case EQUAL:
		car_to_search.input_car(); break;
	}
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
	cars.push_back(defined_car());
}

void AutoShop::sell()
{
	show();
	unsigned to_sell = input(message[SELL_MSG],
		cars.size(), 1U) - 1U;
	cars.erase(cars.begin() + to_sell);
}

void AutoShop::take_request()
{
	menu(shop_menu, SHOP_MENU_SIZE);
	request = input(message[REQUEST_MSG],
		FIND, QUIT);
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
	pause();
}

void AutoShop::sort()
{
	seller.choose_sort_options();
	std::sort(cars.begin(),
		cars.end(), seller);
}

void AutoShop::show()const
{
	show_cars(std::cout, cars);
}

void AutoShop::find()
{
	seller.choose_find_option();
	seller.search_request();
	if (!show_cars(std::cout, cars, seller))
		std::cout << message[NOT_FOUND];
}

void AutoShop::propose_catalog()const
{
	unsigned answer =
		input(message[CAT_ANS], YES, NO);
	if (YES == answer)
	{
		std::ofstream fout(catalog);
		show_cars(fout, cars);
		std::cout << message[CAT_MSG]
			<< catalog << std::endl;
		fout.close();
	}
	pause();
}

bool AutoShop::customer_is_out()const
{
	return request == QUIT;
}