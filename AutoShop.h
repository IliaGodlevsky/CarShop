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
	Seller(const Car& car);
	bool operator()(const Car& first, const Car& second)const;
	bool operator()(const Car& car)const;
	void choose_sort_options();
	void choose_find_option();
private:
	// Pointer to a METHOD
	using Compare = bool(Seller::*)(const Car&, const Car&)const;
	using Coincidence = std::vector<Compare>;
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
	unsigned count_coincidence(const Car& car)const;
	void find_request();
private:
	enum { SORT_OPTIONS = 4, FIND_OPTIONS };
	enum Request { QUIT, NAME, COST, YEAR, POWER, EQUAL };
	static constexpr unsigned SELLER_MENU_SIZE = EQUAL;
	const char* const seller_menu[SELLER_MENU_SIZE] =
	{ "Name","Cost","Year","Power","Car" };
private:
	const Compare compare[SORT_OPTIONS];
	const Compare find[FIND_OPTIONS];
private:
	Coincidence coincidence;
	Car car_to_find;
	Request to_compare; 
	Request to_find;
};

class AutoShop
{
public:
	AutoShop(size_t size = 0, Plant car_gen = nullptr);
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
	void find()const;
private:
	enum { NO, YES };
	enum Char { QUIT, STOCK, SELL, SHOW, SORT, FIND };
	static constexpr unsigned SHOP_MENU_SIZE = FIND;
	const char* const shop_menu[SHOP_MENU_SIZE] =
	{ "Add","Sell","Show","Sort","Find" };
private:
	Char request;
	Park cars;
};
#endif