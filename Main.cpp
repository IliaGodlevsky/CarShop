#include "Functions.h"
#include "Constants.h"
#include "AutoShop.h"

int main()
{
	size_t shop_size = input(shop_msg,
		MAX_SHOP_SIZE, MIN_SHOP_SIZE);
	AutoShop shop(shop_size, plant());
	visit_auto_shop(shop);
}