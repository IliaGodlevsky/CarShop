#pragma once

const int TYPES = 7;

const char* const names[TYPES] = { "Lada","BMW","Geely","Opel","Shkoda","BELAZ","Wolkswagen" };
const int years[TYPES] = { 1990,1995,2000,2005,2010,2015,2019 };
const int costs[TYPES] = { 5000,7000,10000,12000,15000,22000,25000 };
const int powers[TYPES] = { 50,60,70,80,90,120,150 };

enum MINMAX {
	MIN_YEAR = 1990, MAX_YEAR = 2019, 
	MIN_COST = 5000, MAX_COST = 25000,
	MIN_POWER = 50, MAX_POWER = 150
};

const char* const year_msg = "Enter year: ";
const char* const power_msg = "Enter power: ";
const char* const name_msg = "Enter name: ";
const char* const cost_msg = "Enter cost: ";
const char* const sort_msg = "Choose sort rule: ";
const char* const sell_msg = "Choose car number: ";
const char* const request_msg = "Choose option (0 to quit): ";
