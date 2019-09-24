#include "Functions.h"
#include "Constants.h"

int main()
{
	srand(unsigned(time(nullptr)));
	AutoShop shop(CARS, rand_car);
	visit_auto_shop(shop);
}
