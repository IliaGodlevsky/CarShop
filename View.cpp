#include "View.h"
#include "Functions.h"

View::View(bool name, bool cost,
	bool year, bool power, bool car) : states(STATES)
{
	states[0] = name;
	states[1] = cost;
	states[2] = year;
	states[3] = power;
	states[4] = car;
	show[0] = &View::show_name;
	show[1] = &View::show_cost;
	show[2] = &View::show_year;
	show[3] = &View::show_power;
	show[4] = &View::show_car;
}

void View::show_options()
{
	const unsigned QUIT = 0;
	menu(functor_menu, STATES);
	to_show = (Request)input(show_msg, 
		EQUAL, QUIT);
	while (to_show != QUIT)
	{
		states[to_show - 1] = true;
		if (to_show == EQUAL)
			break;
		to_show = (Request)input(show_msg,
			EQUAL, QUIT);
	}
	check_states();
}

void View::show_cars(std::ostream& os,
	const Park& cars) const
{
	unsigned i = 0;
	for (auto& car : cars)
		show_car(os, car, ++i);
}

bool View::show_cars(std::ostream& os,
	const Park& cars,
	const Functor& seller)const
{
	unsigned i = 0;
	unsigned count = 0;
	for (auto& car : cars)
	{
		i++;
		if (seller(car))
		{
			show_car(os, car, i);
			count++;
		}
	}
	return count;
}

void View::show_name(std::ostream& os,const Car& car)const
{
	os << "Name: " << car.name << std::endl;
	
}

void View::show_year(std::ostream& os, const Car& car)const
{
	os << "Year: " << car.year << std::endl;

}

void View::show_cost(std::ostream& os, const Car& car)const
{
	os << "Cost: " << car.cost << " $\n";
}

void View::show_power(std::ostream& os, const Car& car)const
{
	os << "Power: " << car.power << " hp\n";
}

void View::show_car(std::ostream& os, const Car& car)const
{
	for (size_t i = 0; i < STATES - 1; i++)
		(this->*show[i])(os, car);
}

void View::show_car(std::ostream& os,
	const Car& car, unsigned index)const
{
	os << "     " << index << std::endl;
	for (size_t i = 0; i < STATES; i++)
	{
		if (states[i])
			(this->*show[i])(os, car);
	}
	os << std::endl;
}

void View::check_states()
{
	if (*(states.end() - 1))
	{
		for (size_t i = 0; i < STATES - 1; i++)
			states[i] = false;
	}
}