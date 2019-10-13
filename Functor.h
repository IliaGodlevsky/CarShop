#pragma once

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "AutoShop.h"

class Functor
{
public:
	Functor() {}
	virtual void choose_options() = 0;
	virtual bool operator()(const Car& first,
		const Car& second)const = 0;
	virtual bool operator()(const Car& car)const = 0;
};

class Comparator : public Functor
{
public:
	Comparator();
	void choose_options() override;
	bool operator()(const Car& first, 
		const Car& second)const;
private:
	using Compare = bool(Comparator::*)(const Car&,
		const Car&)const;
	// Functions used to compare cars by one of the car's parametre
	bool is_less_name(const Car& first, const Car& second)const;
	bool is_less_cost(const Car& first, const Car& second)const;
	bool is_greater_year(const Car& first, const Car& second)const;
	bool is_greater_power(const Car& first, const Car& second)const;
	bool operator()(const Car& car)const;
private:
	enum { SORT_OPTIONS = 4 };
	Compare compare[SORT_OPTIONS];
	Request to_compare;
};

class Finder : public Functor
{
public:
	Finder();
	void choose_options()override;
	bool operator()(const Car& car)const;
private:
	using Compare = bool(Finder::*)(const Car&,
		const Car&)const;
	// Functions used to find a car by one of the car's parametre
	bool are_same(const Car& first, const Car& second)const;
	bool have_same_name(const Car& first, const Car& second)const;
	bool have_same_cost(const Car& first, const Car& second)const;
	bool have_same_year(const Car& first, const Car& second)const;
	bool have_same_power(const Car& first, const Car& second)const;
	bool operator()(const Car& first, const Car& second)const;
	void find_request();
private:
	enum { FIND_OPTIONS = 5 };
	Compare find[FIND_OPTIONS];
	Request to_find;
	Car car_to_find;
};
#endif