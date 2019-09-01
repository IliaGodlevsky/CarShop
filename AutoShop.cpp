#include <algorithm>

#include "AutoShop.h"

AutoShop::AutoShop(int size, Car(*gen)()): cars(size)
{
	std::generate(cars.begin(), cars.end(), gen());
}

void AutoShop::delivery()
{
	cars.push_back(rand_car());
}

void AutoShop::sell()
{
	cars.pop_back();
}

void AutoShop::menu()const
{

}

void AutoShop::take_request()
{
	request = input();
}

void AutoShop::fulfill_request()
{
	switch (request)
	{
	case ADD:	delivery(); break;
	case POP:	sell();		break;
	case SHOW:	show();		break;
	case SORT:	sort();		break;
	case FIND:	find();		break;
	}
	system("pause");
	system("cls");
}

void AutoShop::sort()
{
	seller.sort_menu();
	int choice = seller.choose_sort_options();
	seller.compare_option(choice);
	std::sort(cars.begin(), cars.end(), seller);
}

void AutoShop::show()const
{
	for (auto& car : cars)
		std::cout << car << std::endl;
}

void AutoShop::find()
{
	seller.search_application();
	std::find_if(cars.begin(), cars.end(), seller);

}

Car rand_car()
{

}