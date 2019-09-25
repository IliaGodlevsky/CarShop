#include "Functions.h"
#include "Constants.h"

int main()
{
	srand(unsigned(time(nullptr)));
	AutoShop shop(CARS, rand_car);
	while (!shop.customer_is_out())
	{
		shop.take_request();
		shop.fulfill_request();
	}
	shop.propose_catalog();
}
