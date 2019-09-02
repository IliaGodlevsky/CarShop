#include "AutoShop.h"
#include "Functions.h"

#include <ctime>

int main()
{
	srand(unsigned(time(nullptr)));
	const int SHOP_SIZE = 10;
	AutoShop shop(SHOP_SIZE, rand_car);
	while (!shop.customer_is_out())
	{
		shop.take_request();
		shop.fulfill_request();
	}
}
