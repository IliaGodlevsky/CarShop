#pragma once

#ifndef FUNCT_H_
#define FUNCT_H_

#include <ctime>
#include <fstream>
#include <random>

#include "AutoShop.h"
#include "Constants.h"

using Strings = std::vector<std::string>;
using Random = std::uniform_int_distribution<unsigned>;

// generating functions
Car rand_car();
Car defined_car();

Plant plant();

// random number generators
unsigned random(unsigned max,
	unsigned min = 0);
unsigned linear(unsigned b = 0,
	unsigned a = 1,
	unsigned x = random(VARIABLE));

// file functions
Strings load_file(std::string filename);
template <typename Stream>
void file_opening(Stream& stream,
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
void table_head(std::ostream& os);

// input functions
unsigned input(const char* msg,
	unsigned up, unsigned  down);
std::string input(const char* msg);
bool error(unsigned choice,
	unsigned up, unsigned down);
std::istream& eatline(std::istream& is);
void menu(const char* const menu[],
	size_t size);
void wait(clock_t seconds = 0);
void system(const size_t cmnds, 
	const char* first...);

void visit_auto_shop(AutoShop& shop);

template <typename Stream>
void file_opening(Stream& stream,
	std::string filename)
{
	stream.open(filename);
	while (!stream.is_open())
		stream.open(input(file_msg));
}
#endif