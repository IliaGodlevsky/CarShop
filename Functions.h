#pragma once

#ifndef FUNCT_H_
#define FUNCT_H_

#include <ctime>

#include "AutoShop.h"
#include "Constants.h"

using Strings = std::vector<std::string>;

Car rand_car();
Car defined_car();
// linear function
unsigned linear(unsigned b = 0,
	unsigned a = 1,
	unsigned x = std::rand() % VARIABLE);
void eatline(std::istream& is);
void pause(clock_t seconds = 0);
Strings load_lines(std::string filename);
void show_car(std::ostream& os, 
	const Car& car, unsigned index);
void show_cars(std::ostream& os,
	const Park& cars);
bool show_cars(std::ostream& os,
	const Park& cars,
	const Seller& seller);
void menu(const char* const menu[],
	size_t size);
unsigned input(const std::string& msg,
	unsigned up, unsigned  down);
std::string input(const std::string& msg);
bool error(unsigned choice,
	unsigned up, unsigned down);
#endif
