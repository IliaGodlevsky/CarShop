#include <algorithm>
#include <fstream>
#include <valarray>

#include "Functions.h"
#include "Constants.h"

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

///// CLASS SELLER METHODS DEFINITIONS /////

Seller::Seller() : Seller(Car())
{

}

Seller::Seller(const Car& car)
	: car_to_find(car),
	compare
	{
	&Seller::is_less_name,
	&Seller::is_less_cost,
	&Seller::is_greater_year,
	&Seller::is_greater_power
	},
	find
	{
	&Seller::have_same_name,
	&Seller::have_same_cost,
	&Seller::have_same_year,
	&Seller::have_same_power,
	&Seller::are_same
	}
{

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

bool Seller::operator()(const Car& car)const
{
	return count_coincidence(car) >= coincidence.size();
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
	to_compare = (Request)input(sort_msg, 
		POWER, NAME);
}

void Seller::choose_find_option()
{
	menu(seller_menu, FIND_OPTIONS);
	to_find = (Request)input(find_msg, 
		EQUAL, QUIT);
	while (to_find)
	{
		coincidence.push_back(find[to_find - 1]);
		find_request();
		to_find = (Request)input(find_msg,
			EQUAL, QUIT);
	}
}

void Seller::find_request()
{
	switch (to_find)
	{
	case NAME:
		car_to_find.name = input(name_msg); 
		break;
	case YEAR:
		car_to_find.year = input(year_msg,
			MAX_YEAR, MIN_YEAR); break;
	case COST:
		car_to_find.cost = input(cost_msg,
			MAX_COST, MIN_COST); break;
	case POWER:
		car_to_find.power = input(power_msg,
			MAX_POWER, MIN_POWER); break;
	case EQUAL:
		car_to_find.input_car(); break;
	}
}

unsigned Seller::count_coincidence(const Car& car)const
{
	unsigned founded = 0;
	for (size_t i = 0; i < coincidence.size(); i++)
		founded += (this->*coincidence[i])(car, car_to_find);
	return founded;
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
		show_cars(std::cout, cars);
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
	Seller seller;
	seller.choose_sort_options();
	std::sort(cars.begin(),
		cars.end(), seller);
}

void AutoShop::show()const
{
	show_cars(std::cout, cars);
}

void AutoShop::find()const
{
	Seller seller;
	seller.choose_find_option();
	if (!show_cars(std::cout, cars, seller))
		std::cout << not_found;
}

void AutoShop::propose_catalog()const
{
	const bool answer =
		input(calalog_answer, YES, NO);
	if (YES == answer)
	{
		std::ofstream fout;
		file_opening(fout, catalog);
		show_cars(fout, cars);
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