#pragma once

#ifndef FUNCT_H_
#define FUNCT_H_

#include <ctime>

#include "AutoShop.h"

namespace shop
{
	shop::Car rand_car();
	shop::Car defined_car();
	void eatline();
	void pause(clock_t seconds = 0);
	void show_cars(std::ostream& os,
		const Park& cars);
	bool show_cars(std::ostream& os,
		const Park& cars, const Seller& seller);
	void menu(const char* const menu[], 
		size_t size);
	unsigned input(const char* msg,
		unsigned up, unsigned  down);
	std::string input(const char* msg);
	bool error(unsigned choice,
		unsigned up, unsigned down);
}
#endif
