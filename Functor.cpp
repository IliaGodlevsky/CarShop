#include "Functor.h"
#include "Functions.h"

Comparator::Comparator()
{
	compare[0] = &Comparator::is_less_name;
	compare[1] = &Comparator::is_less_cost;
	compare[2] = &Comparator::is_greater_year;
	compare[3] = &Comparator::is_greater_power;
}

void Comparator::choose_options()
{
	menu(functor_menu, SORT_OPTIONS);
	to_compare = (Request)input(sort_msg,
		POWER, NAME);
}

bool Comparator::operator()(const Car& first, const Car& second)const
{
	return (this->*compare[to_compare - 1])(first, second);
}

bool Comparator::is_less_name(const Car& first, const Car& second)const
{
	return first.name < second.name;
}

bool Comparator::is_less_cost(const Car& first, const Car& second)const
{
	return first.cost < second.cost;
}

bool Comparator::is_greater_year(const Car& first, const Car& second)const
{
	return first.year > second.year;
}

bool Comparator::is_greater_power(const Car& first, const Car& second)const
{
	return first.power > second.power;
}

Finder::Finder()
{
	find[0] = &Finder::have_same_name;
	find[1] = &Finder::have_same_cost;
	find[2] = &Finder::have_same_year;
	find[3] = &Finder::have_same_power;
	find[4] = &Finder::are_same;
}

bool Finder::operator()(const Car& first)const
{
	return operator()(first, car_to_find);
}

bool Finder::are_same(const Car& first, const Car& second)const
{
	return first == second;
}

bool Finder::have_same_name(const Car& first, const Car& second)const
{
	return first.name == second.name;
}

bool Finder::have_same_cost(const Car& first, const Car& second)const
{
	return first.cost == second.cost;
}

bool Finder::have_same_year(const Car& first, const Car& second)const
{
	return first.year == second.year;
}

bool Finder::have_same_power(const Car& first, const Car& second)const
{
	return first.power == second.power;
}

bool Finder::operator()(const Car& first, const Car& second)const
{
	return (this->*find[to_find - 1])(first, second);
}

void Finder::find_request()
{
	switch (to_find)
	{
	case NAME:
		car_to_find.name = input(name_msg);
		break;
	case YEAR:
		car_to_find.year = input(year_msg,
			MAX_YEAR, MIN_YEAR); break;
	case COST:
		car_to_find.cost = input(cost_msg,
			MAX_COST, MIN_COST); break;
	case POWER:
		car_to_find.power = input(power_msg,
			MAX_POWER, MIN_POWER); break;
	case EQUAL:
		car_to_find.input_car(); break;
	}
}

void Finder::choose_options()
{
	menu(functor_menu, FIND_OPTIONS);
	to_find = (Request)input(find_msg,
		EQUAL, NAME);
	find_request();
}