#pragma once

#include <iostream>

#include "AutoShop.h"
#include "Constants.h"

#ifndef VIEW_H_
#define VIEW_H_

class View
{
public:
	View(bool name = false, bool cost = false, 
		bool year = false, bool power = false,
		bool car = false);
	void show_options();
	void show_cars(std::ostream& os,
		const Park& cars)const;
	bool show_cars(std::ostream& os,
		const Park& cars,
		const Functor& seller)const;
private:
	using States = std::vector<bool>;
	using Show = void(View::*)(std::ostream&, const Car&)const;
	void show_name(std::ostream& os, const Car& car)const;
	void show_year(std::ostream& os, const Car& car)const;
	void show_cost(std::ostream& os, const Car& car)const;
	void show_power(std::ostream& os, const Car& car)const;
	void show_car(std::ostream&os, const Car& car)const;
	void show_car(std::ostream& os,
		const Car& car, unsigned index)const;
	void check_states();
private:
	static const unsigned STATES = 5;
	Show show[STATES];
	Request to_show;
	States states;
};

#endif
