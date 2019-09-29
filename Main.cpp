#include "Functions.h"
#include "Constants.h"
#include "AutoShop.h"

int main()
{
	srand(unsigned(time(nullptr)));
	size_t shop_size = input(shop_msg, 
		MAX_SHOP_SIZE, MIN_SHOP_SIZE);
	AutoShop shop(shop_size, rand_car);
	while (!shop.customer_is_out())
	{
		shop.take_request();
		shop.fulfill_request();
	}
	shop.propose_catalog();
}