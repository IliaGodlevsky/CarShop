#pragma once

#ifndef FUNCT_H_
#define FUNCT_H_

#include <ctime>

#include "AutoShop.h"

namespace shop
{
	shop::Car rand_car();
	shop::Car defined_car();
	int input(const char* msg,
		int up, int down);
	void eatline();
	bool err(int choice,
		int up, int down);
	void pause(clock_t seconds = 0);
	void show_cars(std::ostream& os,
		const std::vector<shop::Car>& cars);
}
#endif
