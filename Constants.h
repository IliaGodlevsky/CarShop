#pragma once

#ifndef CONST_H_
#define CONST_H_

#include <string>

enum {
	VARIABLE = 29,
	YEAR_ADD = 1991,
	COST_MULT = 1000,
	POW_MULT = 5,
	POW_ADD = 50
};

enum {
	MIN_SHOP_SIZE = 5, MAX_SHOP_SIZE = 25,
	MIN_YEAR = 1991, MAX_YEAR = 2019,
	MIN_COST = 1000, MAX_COST = 1000000,
	MIN_POWER = 50, MAX_POWER = 300
};

const std::string not_found = "Nothing was found\n";
const std::string year_msg = "Enter year: ";
const std::string power_msg = "Enter power: ";
const std::string name_msg = "Enter name: ";
const std::string cost_msg = "Enter cost: ";
const std::string sort_msg = "Choose sort option: ";
const std::string find_msg = "Choose find option: ";
const std::string sell_msg = "Choose car number: ";
const std::string shop_msg = "Enter shop size: ";
const std::string request_msg = "Choose option (0 to quit): ";
const std::string calalog_answer = "Do you want to get our "
"car catalog (1 - Yes, 0 - No): ";
const std::string catalog_msg = "You can find your "
"catalog in ";
const std::string filename = "Car names.txt";
const std::string catalog = "Catalog.txt";
#endif