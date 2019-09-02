#pragma once

#ifndef CONST_H_
#define CONST_H_

namespace shop
{
	const unsigned TYPES = 29;

	const char* const names[TYPES] = { "Audi","Cadillac",
	"Lada","BMW","Geely","Opel","Skoda","BELAZ","Volkswagen",
	"Caterpillar","Benz","Mersedes","Bugatti","Daewoo","Dakar",
	"Ferrari","Fiat","Ford","Honda","Hyundai","Jaguar","Jeep",
	"Komatsu","Zotye","Mathis","Mitsubishi","Lifan","Lamborghini",
	"Hitachi" };

	const unsigned years[TYPES] = { 1991,1992,1993,1994,
	1995,1996,1997,1998,1999,2000,2001,2002,2003,2004,
	2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,
	2015,2016,2017,2018,2019 };

	const unsigned costs[TYPES] = { 1000,2000,3000,4000,5000,
	6000,7000,8000,9000,10000,11000,12000,13000,14000,
	15000,16000,17000,18000,19000,20000,21000,22000,23000,
	24000,25000,26000,27000,28000,29000 };

	const unsigned powers[TYPES] = { 50,55,60,65,70,75,80,85,
	90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,
	165,170,175,180,185,190 };

	enum Minmax {
		MIN_YEAR = 1991, MAX_YEAR = 2019,
		MIN_COST = 1000, MAX_COST = 1000000,
		MIN_POWER = 50, MAX_POWER = 300
	};

	const char* const year_msg = "Enter year: ";
	const char* const power_msg = "Enter power: ";
	const char* const name_msg = "Enter name: ";
	const char* const cost_msg = "Enter cost: ";
	const char* const sort_msg = "Choose sort option: ";
	const char* const find_msg = "Choose find option: ";
	const char* const sell_msg = "Choose car number: ";
	const char* const request_msg = "Choose option (0 to quit): ";
	const char* const calalog_answer = "Do you want to get our\n"
		"car catalog (1 - Yes, 0 - No): ";
	const char* const catalog = "Catalog.txt";
}
#endif