#ifndef CAR_H_
#define CAR_H_

#include <iostream>
#include <string>

#include "Seller.h"

class Car
{
	friend class Seller;
public:
	Car();
	Car(const char* name, int year,
		int cost, double power);
	friend std::ostream& operator <<
		(std::ostream& os, const Car& car);
	friend std::istream& operator >>
		(std::istream& is, Car& car);
	bool operator==(const Car& first)const;
private:
	std::string name;
	int year;
	int cost;
	int power;
};
#endif
