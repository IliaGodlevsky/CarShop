#pragma once

#ifndef CONST_H_
#define CONST_H_

enum 
{
	VARIABLE = 29,
	YEAR_ADD = 1991,
	COST_MULT = 1000,
	POW_MULT = 5,
	POW_ADD = 50
};

enum 
{
	MIN_SHOP_SIZE = 5, MAX_SHOP_SIZE = 25,
	MIN_YEAR = 1991, MAX_YEAR = 2019,
	MIN_COST = 1000, MAX_COST = 1000000,
	MIN_POWER = 50, MAX_POWER = 300
};

enum 
{
	
	NOT_FOUND,YEAR_MSG,POWER_MSG, NAME_MSG,COST_MSG, SORT_MSG,
	FIND_MSG, SELL_MSG, SHOP_MSG, REQUEST_MSG, CAT_ANS, CAT_MSG
};

const char* const filename = "Car names.txt";
const char* const catalog = "Catalog.txt";
const char* const messages = "Messages.txt";
#endif