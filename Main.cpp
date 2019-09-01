#include "AutoShop.h"
#include "Seller.h"
#include "Car.h"

#include <ctime>

const int SHOP_SIZE = 10;

int main()
{
	srand(unsigned(time(nullptr)));
	AutoShop shop(SHOP_SIZE, rand_car);
	while (!shop.customer_is_out())
	{
		shop.take_request();
		shop.fulfill_request();
	}
}
