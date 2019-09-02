#pragma once

#ifndef AUTO_SHOP_H_
#define AUTO_SHOP_H_

#include <vector>
#include <iostream>
#include <string>

class Seller;

class Car
{
	friend class Seller;
public:
	Car();
	Car(const std::string& name, int year,
		int cost, int power);
	friend std::ostream& operator <<
		(std::ostream& os, const Car& car);
	friend std::istream& operator >>
		(std::istream& is, Car& car);
	bool operator==(const Car& first)const;
private:
	std::string name;
	int year;
	int cost;
	int power;
};

class Seller
{
public:
	Seller();
	bool operator()(const Car& first, const Car& second)const;
	bool operator()(const Car& first)const;
	void sort_menu()const;
	void choose_sort_options();
	void search_request();
private:
	using Compare = bool(Seller::*)(const Car&, const Car&)const;
	bool name_cmp(const Car& first, const Car& second)const;
	bool cost_cmp(const Car& first, const Car& second)const;
	bool year_cmp(const Car& first, const Car& second)const;
	bool power_cmp(const Car& first, const Car& second)const;
	bool equal(const Car& first, const Car& second)const;
private:
	static const int OPTIONS = 5;
	enum { NAME = 1, POWER = 4 };
	Compare compare[OPTIONS];
	int to_compare;
	Car to_search;
};

class AutoShop
{
	using RandomCar = Car(*)();
public:
	AutoShop(int size, RandomCar car);
	void take_request();
	void fulfill_request();
	bool customer_is_out()const;
private:
	void menu()const;
	void show()const;
	void sort();
	void stock();
	void sell();
	void find();
private:
	enum { QUIT, ADD, POP, 
		SHOW, SORT, FIND };
	int request = FIND;
	std::vector<Car> cars;
	Seller seller;
};

#endif