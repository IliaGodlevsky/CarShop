#include "AutoShop.h"
#include "Functions.h"
#include "Constants.h"

int main()
{
	std::srand(unsigned(std::time(nullptr)));
	shop::AutoShop shop(shop::SHOP_SIZE, shop::rand_car);
	while (!shop.customer_is_out())
	{
		shop.take_request();
		shop.fulfill_request();
	}
	shop.propose_catalog();
}
