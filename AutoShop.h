#ifndef SHOP_H_
#define SHOP_H_

#include <vector>

#include "Car.h"

Car rand_car();

class AutoShop
{
public:
	AutoShop(int size,Car(*gen)());
	void take_request();
	void fulfill_request();
	bool customer_is_out()const;
private:
	void menu()const;
	int input()const;
	void sort();
	void delivery();
	void sell();
	void show()const;
	void find();
private:
	enum { QUIT, ADD, POP, 
		SHOW, SORT, FIND };
	int request;
	std::vector<Car> cars;
	Seller seller;
};

#endif
