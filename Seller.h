#ifndef SELLER_H_
#define SELLER_H_

#include "Car.h"
#include "AutoShop.h"

class Seller
{
	friend class AutoShop;
public:
	Seller();
	bool operator()(const Car& first, const Car& second)const;
	bool operator()(const Car& first)const;
	void compare_option(int to_compare);
private:
	using Compare = bool(Seller::*)(const Car&, const Car&)const;
	bool name_cmp(const Car& first, const Car& second)const;
	bool cost_cmp(const Car& first, const Car& second)const;
	bool year_cmp(const Car& first, const Car& second)const;
	bool power_cmp(const Car& first, const Car& second)const;
	bool equal(const Car& first, const Car& second)const;
	void sort_menu()const;
	int choose_sort_options()const;
	void search_application();
private:
	Car to_search;
	enum { OPTIONS = 5 };
	enum { NAME, COST, YEAR, POWER, EQUAL };
	int to_compare;
	Compare compare[OPTIONS];
};
#endif
