#include "Functions.h"
#include "Constants.h"

int main()
{
	srand(unsigned(time(nullptr)));
	const unsigned int SHOP_SIZE = 9U;
	AutoShop shop(SHOP_SIZE, rand_car);
	visit_auto_shop(shop);
}
