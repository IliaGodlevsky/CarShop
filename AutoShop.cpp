#include <algorithm>
#include <fstream>

#include "AutoShop.h"
#include "Functions.h"
#include "Constants.h"

namespace shop
	///// CLASS CAR METHODS DEFINITIONS /////
{
	Car::Car() : name("Car"), year(1900), cost(0), power(1) {}

	Car::Car(const std::string& name, unsigned year,
		unsigned cost, unsigned power) :
		name(name), year(year),
		cost(cost), power(power) {}

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
		getline(is, car.name);
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

	///// CLASS SELLER METHODS DEFINITIONS /////

	Seller::Seller()
	{
		compare[0] = &Seller::name_cmp;
		compare[1] = &Seller::cost_cmp;
		compare[2] = &Seller::year_cmp;
		compare[3] = &Seller::power_cmp;
		find[0] = &Seller::name_equal;
		find[1] = &Seller::cost_equal;
		find[2] = &Seller::year_equal;
		find[3] = &Seller::power_equal;
		find[4] = &Seller::equal;
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
		return (this->*find[to_find - 1])(first, to_search);
	}

	bool Seller::equal(const Car& first, const Car& second)const
	{
		return first == second;
	}

	bool Seller::name_equal(const Car& first, const Car& second)const
	{
		return first.name == second.name;
	}

	bool Seller::cost_equal(const Car& first, const Car& second)const
	{
		return first.cost == second.cost;
	}

	bool Seller::year_equal(const Car& first, const Car& second)const
	{
		return first.year == second.year;
	}

	bool Seller::power_equal(const Car& first, const Car& second)const
	{
		return first.power == second.power;
	}

	void Seller::choose_sort_options()
	{
		to_compare = input(sort_msg,
			POWER, NAME);
	}

	void Seller::choose_find_option()
	{
		to_find = input(find_msg, EQUAL, NAME);
	}

	void Seller::search_request()
	{
		switch (to_find)
		{
		case NAME:  std::cout << name_msg; getline(std::cin, to_search.name); break;
		case YEAR:  to_search.year = input(year_msg, MAX_YEAR, MIN_YEAR);	  break;
		case COST:  to_search.cost = input(cost_msg, MAX_COST, MIN_COST);	  break;
		case POWER: to_search.power = input(power_msg, MAX_POWER, MIN_POWER); break;
		case EQUAL: std::cin >> to_search; break;
		}
	}

	///// CLASS AUTOSHOP METHODS DEFINITIONS /////

	AutoShop::AutoShop(size_t size, RandomCar car)
		: request(FIND)
	{
		cars.resize(size);
		std::generate(cars.begin(),
			cars.end(), car);
	}

	void AutoShop::stock()
	{
		cars.push_back(defined_car());
	}

	void AutoShop::sell()
	{
		show(std::cout);
		size_t to_sell = input(sell_msg, cars.size(), 1) - 1;
		cars.erase(cars.begin() + to_sell);
	}

	void AutoShop::take_request()
	{
		menu(shop_menu, SHOP_MENU_SIZE);
		request = input(request_msg, FIND, QUIT);
	}

	void AutoShop::fulfill_request()
	{
		switch (request)
		{
		case ADD:  stock();			break;
		case POP:  sell();			break;
		case SHOW: show(std::cout);	break;
		case SORT: sort();			break;
		case FIND: find();			break;
		}
		pause();
	}

	void AutoShop::sort()
	{
		menu(seller_menu, SELLER_MENU_SIZE - 1);
		seller.choose_sort_options();
		std::sort(cars.begin(),
			cars.end(), seller);
	}

	void AutoShop::show(std::ostream& os)const
	{
		show_cars(os, cars);
	}

	void AutoShop::find()
	{
		menu(seller_menu, SELLER_MENU_SIZE);
		seller.choose_find_option();
		seller.search_request();
		Park found_cars = find_cars();
		if (found_cars.empty())
			std::cout << "Nothing was found\n";
		else
			show_cars(std::cout, found_cars);
	}

	AutoShop::Park AutoShop::find_cars()const
	{
		Park found_cars;
		auto found = std::find_if(cars.begin(),
			cars.end(), seller);
		while (found != cars.end())
		{
			found_cars.push_back(*found);
			found = std::find_if(found + 1,
				cars.end(), seller);
		}
		return found_cars;
	}

	void AutoShop::propose_catalog()const
	{
		unsigned answer = input(calalog_answer, YES, NO);
		if (answer == YES)
		{
			std::ofstream fout(catalog);
			show(fout);
			std::cout << "You can find your "
				"catalog in " << catalog << std::endl;
			fout.close();
		}
		pause();
	}

	bool AutoShop::customer_is_out()const
	{
		return request == QUIT;
	}
}