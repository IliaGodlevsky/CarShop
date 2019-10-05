#pragma once

#ifndef FUNCT_H_
#define FUNCT_H_

#include <ctime>
#include <fstream>

#include "AutoShop.h"
#include "Constants.h"

using Strings = std::vector<std::string>;

// generating functions
Car rand_car();
Car defined_car();

// linear function
unsigned linear(unsigned b = 0,
	unsigned a = 1,
	unsigned x = std::rand() % VARIABLE);

// file functions
Strings load_file(std::string filename);
void file_opening(std::ifstream& is,
	std::string filename);
Strings file_reading(std::ifstream& is);

// output functions
void show_car(std::ostream& os, 
	const Car& car, unsigned index);
void show_cars(std::ostream& os,
	const Park& cars);
bool show_cars(std::ostream& os,
	const Park& cars,
	const Seller& seller);

// input functions
unsigned input(const char* msg,
	unsigned up, unsigned  down);
std::string input(const char* msg);
bool error(unsigned choice,
	unsigned up, unsigned down);
void eatline(std::istream& is);
void menu(const char* const menu[],
	size_t size);
void wait(clock_t seconds = 0);
void system(size_t cmnds, 
	const char* first...);

void visit_auto_shop(AutoShop& shop);
#endif
