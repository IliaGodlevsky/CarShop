#pragma once

#ifndef AUTO_SHOP_H_
#define AUTO_SHOP_H_

#include <vector>
#include <iostream>
#include <string>

class Seller;
class Car;

using Park = std::vector<Car>;
using Plant = Car(*)();

class Car
{
	friend class Seller;
public:
	Car();
	Car(const std::string& name, unsigned year,
		unsigned cost, unsigned power);
	Car(const Car&) = default;
	Car(Car&&) = default;
	Car& operator=(const Car&) = default;
	Car& operator=(Car&&) = default;
	friend std::ostream& operator <<
		(std::ostream& os, const Car& car);
	Car& input_car();
	bool operator==(const Car& first)const;
	~Car() {}
private:
	std::string name;
	unsigned year;
	unsigned cost;
	unsigned power;
};

// Functor class Seller
class Seller
{
public:
	Seller();
	bool operator()(const Car& first, const Car& second)const;
	bool operator()(const Car& first)const;
	void choose_sort_options();
	void choose_find_option();
	void search_request();
private:
	// Pointer to a METHOD
	using Compare = bool(Seller::*)(const Car&, const Car&)const;
	// Functions used to compare cars by one of the car's parametre
	bool is_less_name(const Car& first, const Car& second)const;
	bool is_less_cost(const Car& first, const Car& second)const;
	bool is_greater_year(const Car& first, const Car& second)const;
	bool is_greater_power(const Car& first, const Car& second)const;
	// Functions used to find a car by one of the car's parametre
	bool are_same(const Car& first, const Car& second)const;
	bool have_same_name(const Car& first, const Car& second)const;
	bool have_same_cost(const Car& first, const Car& second)const;
	bool have_same_year(const Car& first, const Car& second)const;
	bool have_same_power(const Car& first, const Car& second)const;
private:
	enum { SORT_OPTIONS = 4, FIND_OPTIONS };
	enum { NAME = 1, COST, YEAR, POWER, EQUAL };
        static const unsigned SELLER_MENU_SIZE = EQUAL;
	const char* const seller_menu[SELLER_MENU_SIZE] =
	{ "By name","By cost","By year","By power","By car" };
private:
	Compare compare[SORT_OPTIONS];
	Compare find[FIND_OPTIONS];
	unsigned to_compare; 
	unsigned to_find;
	Car car_to_search;
};

class AutoShop
{
public:
	AutoShop(size_t size, Plant car_gen);
	AutoShop() {}
	AutoShop(const AutoShop&) = default;
	AutoShop(AutoShop&&) = default;
	AutoShop& operator=(const AutoShop&) = default;
	AutoShop& operator=(AutoShop&&) = default;
	~AutoShop() {}
public:
	void take_request();
	void fulfill_request();
	void propose_catalog()const;
	bool customer_is_out()const;
private:
	void show()const;
	void sort();
	void stock();
	void sell();
	void find();
private:
	enum { NO, YES };
	enum { QUIT, STOCK, SELL, SHOW, SORT, FIND };
	static const unsigned SHOP_MENU_SIZE = FIND;
	const char* const shop_menu[SHOP_MENU_SIZE] =
	{ "Add","Sell","Show","Sort","Find" };
private:
	unsigned request;
	Park cars;
	Seller seller;
};
#endif
