#include <algorithm>
#include <fstream>

#include "Functions.h"
#include "Constants.h"

///// CLASS CAR METHODS DEFINITIONS /////

bool Car::is_year = false;
bool Car::is_cost = false;
bool Car::is_power = false;


Car::Car() : name("Car"), year(MIN_YEAR),
cost(MIN_COST), power(MIN_POWER) {}

Car::Car(const std::string& name, unsigned year,
	unsigned cost, unsigned power) :
	name(name), year(year),
	cost(cost), power(power) {}

std::ostream& operator <<(std::ostream& os, const Car& car)
{
	os << "Name: " << car.name << std::endl;
	if (car.is_year)
		os << "Year: " << car.year << std::endl;
	if(car.is_cost)
		os << "Cost: " << car.cost << " $\n";
	if(car.is_power)
		os << "Power: " << car.power << " hp\n";
	return os;
}

Car& Car::input_car()
{
	name = input(name_msg);
	year = input(year_msg, MAX_YEAR, MIN_YEAR);
	power = input(power_msg, MAX_POWER, MIN_POWER);
	cost = input(cost_msg, MAX_COST, MIN_COST);
	return *this;
}

void Car::set_display(bool is_year_,
	bool is_cost_, bool is_power_)
{
	is_year = is_year_;
	is_cost = is_cost_;
	is_power = is_power_;
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
	return (this->*find[to_find - 1])(first, car_to_find);
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
		EQUAL, NAME);
}

void Seller::find_request()
{
	switch (to_find)
	{
	case NAME:
		car_to_find.name = input(name_msg); break;
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
	unsigned to_sell = input(sell_msg,
		cars.size(), 1U) - 1U;
	cars.erase(cars.begin() + to_sell);
}

void AutoShop::take_request()
{
	menu(shop_menu, SHOP_MENU_SIZE);
	request = (Char)input(request_msg,
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
	wait();
}

void AutoShop::sort()
{
	seller.choose_sort_options();
	std::sort(cars.begin(),
		cars.end(), seller);
}

void AutoShop::show()const
{
	show_options();
	show_cars(std::cout, cars);
}

void AutoShop::show_options()const
{
	bool is_year = false;
	bool is_cost = false;
	bool is_power = false;
	Show show_mode = YEAR;
	menu(show_menu, SHOW_MENU_SIZE);
	while (show_mode != QUIT)
	{
		show_mode = (Show)input(show_msg, 
			ALL, QUIT);
		switch (show_mode)
		{
		case YEAR: is_year = true; break;
		case COST: is_cost = true; break;
		case POWER: is_power = true; break;
		case ALL: is_year = is_power = 
			is_cost = true; goto exit;
		}
	}
	exit:
	Car::set_display(is_year, 
		is_cost, is_power);
}

void AutoShop::find()
{
	seller.choose_find_option();
	seller.find_request();
	if (!show_cars(std::cout, cars, seller))
		std::cout << not_found;
}

void AutoShop::propose_catalog()const
{
	unsigned answer =
		input(calalog_answer, YES, NO);
	if (YES == answer)
	{
		std::ofstream fout(catalog);
		show_options();
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