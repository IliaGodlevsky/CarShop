#pragma once

#ifndef CONST_H_
#define CONST_H_

constexpr unsigned CMNDS = 2;

// linear function constants
enum {
	VARIABLE = 28,
	YEAR_ADD = 1991,
	COST_MULT = 1000,
	POW_MULT = 5,
	POW_ADD = 50
};

// range constants
enum {
	MIN_SHOP_SIZE = 5, MAX_SHOP_SIZE = 1000,
	MIN_YEAR = 1991, MAX_YEAR = 2019,
	MIN_COST = 1000, MAX_COST = 1000000,
	MIN_POWER = 50, MAX_POWER = 300
};

// message constants
const char* const not_found = "\aNothing was found\n";
const char* const year_msg = "Enter year: ";
const char* const power_msg = "Enter power: ";
const char* const name_msg = "Enter name: ";
const char* const cost_msg = "Enter cost: ";
const char* const file_msg = "Enter file name: ";
const char* const sort_msg = "Choose sort option: ";
const char* const find_msg = "Choose find option: ";
const char* const sell_msg = "Choose car number: ";
const char* const shop_msg = "Enter shop size: ";
const char* const request_msg = "Choose option (0 to quit): ";
const char* const calalog_answer = "Do you want to get our "
"car catalog (1 - Yes, 0 - No): ";
const char* const empty_msg = "\aThere is no any car in autoshop!\n";
const char* const add_msg = "How do you want to add a car?: ";
const char* const catalog_msg = "You can find your "
"catalog in ";

// system commands
const char* const pause = "pause";
const char* const cls = "cls";

// filenames
const char* const car_names = "Car names.txt";
const char* const catalog = "Catalog.txt";
#endif