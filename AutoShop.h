#pragma once

#ifndef AUTO_SHOP_H_
#define AUTO_SHOP_H_

#include <vector>
#include <iostream>
#include <string>

enum Request { NAME = 1, COST, YEAR, POWER, EQUAL };
static constexpr unsigned MENU_SIZE = EQUAL;
const char* const functor_menu[MENU_SIZE] =
{ "By name","By cost","By year","By power","By car" };

class Car;

using Park = std::vector<Car>;
using Plant = Car(*)();

class Car
{
	friend class Comparator;
	friend class Finder;
	friend class View;
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