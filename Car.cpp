#include <cstring>

#include "Car.h"

Car::Car()
{

}

Car::Car(const char* name, int year,
	int cost, double power) :
	name(name), year(year), cost(cost), power(power)
{
	
}

std::ostream& operator <<(std::ostream& os, const Car& car)
{
	os << "Model: " << car.name << std::endl;
	os << "Year: " << car.year << std::endl;
	os << "Cost: " << car.cost << std::endl;
	os << "Power: " << car.power << std::endl;
	return os;
}

std::istream& operator >> (std::istream& is, Car& car)
{
	std::cout << "Enter name: ";
	is >> car.name;

}

bool Car::operator==(const Car& first)const
{
	return
		name == first.name &&
		year == first.year &&
		cost == first.cost &&
		power ==first.power;
}