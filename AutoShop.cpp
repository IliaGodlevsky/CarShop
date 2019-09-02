#include <algorithm>

#include "AutoShop.h"
#include "Functions.h"
#include "Constants.h"

Car::Car() : name("Car"), year(1900), cost(0), power(1)
{
	
}

Car::Car(const std::string& name, int year,
	int cost, int power) :
	name(name), year(year), cost(cost), power(power)
{

}

std::ostream& operator <<(std::ostream& os, const Car& car)
{
	os << "Name: " << car.name << std::endl;
	os << "Year: " << car.year << std::endl;
	os << "Cost: " << car.cost << std::endl;
	os << "Power: " << car.power << std::endl;
	return os;
}

std::istream& operator >> (std::istream& is, Car& car)
{
	std::cout << name_msg;
	is >> car.name;
	car.year = input(year_msg, MAX_YEAR, MIN_YEAR);
	car.power = input(power_msg, MAX_POWER, MIN_POWER);
	car.cost = input(cost_msg, MAX_COST, MIN_COST);
	return is;
}

bool Car::operator==(const Car& first)const
{
	return
		name == first.name &&
		year == first.year &&
		cost == first.cost &&
		power == first.power;
}

Seller::Seller()
{
	compare[0] = &Seller::name_cmp;
	compare[1] = &Seller::cost_cmp;
	compare[2] = &Seller::year_cmp;
	compare[3] = &Seller::power_cmp;
	compare[4] = &Seller::equal;
}
bool Seller::operator()(const Car& first, const Car& second)const
{
	return (this->*compare[to_compare - 1])(first, second);
}

bool Seller::name_cmp(const Car& first, const Car& second)const
{
	return first.name < second.name;
}

bool Seller::cost_cmp(const Car& first, const Car& second)const
{
	return first.cost < second.cost;
}

bool Seller::year_cmp(const Car& first, const Car& second)const
{
	return first.year > second.year;
}

bool Seller::power_cmp(const Car& first, const Car& second)const
{
	return first.power > second.power;
}

bool Seller::operator()(const Car& first)const
{
	return to_search == first;
}

bool Seller::equal(const Car& first, const Car& second)const
{
	return first == second;
}

void Seller::compare_option(int to_compare)
{
	this->to_compare = to_compare;
}

void Seller::sort_menu()const
{
	std::cout << "1. By name   2. By cost\n";
	std::cout << "3. By year   4. By power\n";
}

void Seller::choose_sort_options()
{
	to_compare = input(sort_msg, POWER, NAME);
}

void Seller::search_request()
{
	std::cin >> to_search;
}

AutoShop::AutoShop(int size, RandomCar car)
{
	cars.resize(size);
	std::generate(cars.begin(), 
		cars.end(), car);
}

void AutoShop::delivery()
{
	cars.push_back(defined_car());
}

void AutoShop::sell()
{
	show();
	int to_sell = input(sell_msg, cars.size(), 1) - 1;
	cars.erase(cars.begin() + to_sell);
}

void AutoShop::menu()const
{
	std::cout << "1. Add    2. Sell\n";
	std::cout << "3. Show   4. Sort\n";
	std::cout << "5. Find\n";
}

void AutoShop::take_request()
{
	menu();
	request = input(request_msg, FIND, QUIT);
}

void AutoShop::fulfill_request()
{
	switch (request)
	{
	case ADD:	delivery(); break;
	case POP:	sell();		break;
	case SHOW:	show();		break;
	case SORT:	sort();		break;
	case FIND:	find();		break;
	}
	pause();
}

void AutoShop::sort()
{
	seller.sort_menu();
	seller.choose_sort_options();
	std::sort(cars.begin(), 
		cars.end(), seller);
}

void AutoShop::show()const
{
	for (auto& car : cars)
		std::cout << car << std::endl;
}

void AutoShop::find()
{
	seller.search_request();
	auto found = std::find_if(cars.begin(), 
		cars.end(), seller);
	if (found == cars.end())
		std::cout << "Nothing was found\n";
	else
		std::cout << "There is such a car\n";
}

bool AutoShop::customer_is_out()const
{
	return request == QUIT;
}

