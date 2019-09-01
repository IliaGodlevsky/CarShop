#include <cstring>

#include "Seller.h"

Seller::Seller()
{
	compare[0] = name_cmp;
	compare[1] = cost_cmp;
	compare[2] = year_cmp;
	compare[3] = power_cmp;
	compare[4] = equal;
}
bool Seller::operator()(const Car& first, const Car& second)const
{
	return (this->*compare[to_compare])(first, second);
}

bool Seller::name_cmp(const Car& first, const Car& second)const
{
	return first.name > second.name;
}

bool Seller::cost_cmp(const Car& first, const Car& second)const
{
	return first.cost < second.cost;
}

bool Seller::year_cmp(const Car& first, const Car& second)const
{
	return first.year < second.year;
}

bool Seller::power_cmp(const Car& first, const Car& second)const
{
	return first.power < second.power;
}

bool Seller::equal(const Car& first, const Car& second)const
{
	return first == second;
}

void Seller::compare_option(int to_compare)
{
	this->to_compare = to_compare;
}

void Seller::sort_menu()const
{

}

int Seller::choose_sort_options()const
{

}

void Seller::search_application()
{
	std::cin >> to_search;
}