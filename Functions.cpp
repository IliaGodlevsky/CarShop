#include <iostream>
#include <ctime>

#include "Functions.h"
#include "Constants.h"

int input(const char* msg, int up, int down)
{
	int choice;
	std::cout << msg;
	std::cin >> choice;
	while (err(choice, up, down))
	{
		eatline();
		std::cout << msg;
		std::cin >> choice;
	}
	eatline();
	return int(choice);
}
void eatline()
{
	std::cin.clear();
	while (!iscntrl(std::cin.get()))
		continue;
}
bool err(int choice, int up, int down)
{
	return std::cin.fail() ||
		choice > up || choice < down;
}
void pause(int seconds)
{
	clock_t start = clock();
	while (clock() - start <
		seconds* CLOCKS_PER_SEC)
		continue;
	system("pause");
	system("cls");
}

Car rand_car()
{
	std::string name = names[rand() % TYPES];
	int year = years[rand() % TYPES];
	int cost = costs[rand() % TYPES];
	int power = powers[rand() % TYPES];
	return Car(name, year, cost, power);
}

Car defined_car()
{
	Car temp;
	std::cin >> temp;
	return temp;
}