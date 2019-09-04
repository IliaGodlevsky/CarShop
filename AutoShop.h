#pragma once

#ifndef AUTO_SHOP_H_
#define AUTO_SHOP_H_

#include <vector>
#include <iostream>
#include <string>

namespace shop
{
	class Seller;
	class Car;

	using Park = std::vector<Car>;
	using Plant = Car(*)();

	class Car
	{
		friend class Seller;
	public:
		Car();
		Car(const std::string& name, unsigned year,
			unsigned cost, unsigned power);
		Car(const Car& car) = default;
		Car(Car&& car) = default;
		Car& operator=(const Car& car) = default;
		Car& operator=(Car&& car) = default;
		friend std::ostream& operator <<
			(std::ostream& os, const Car& car);
		void input_car();
		bool operator==(const Car& first)const;
		~Car() {}
	private:
		std::string name;
		unsigned year;
		unsigned cost;
		unsigned power;
	};

	// Functor class Seller
	class Seller
	{
	public:
		Seller();
		bool operator()(const Car& first, const Car& second)const;
		bool operator()(const Car& first)const;
		void choose_sort_options();
		void choose_find_option();
		void search_request();
	private:
		// Pointer to a METHOD
		using Compare = bool(Seller::*)(const Car&, const Car&)const;
		using Find = Compare;
		bool name_cmp(const Car& first, const Car& second)const;
		bool cost_cmp(const Car& first, const Car& second)const;
		bool year_cmp(const Car& first, const Car& second)const;
		bool power_cmp(const Car& first, const Car& second)const;
		bool equal(const Car& first, const Car& second)const;
		bool name_equal(const Car& first, const Car& second)const;
		bool cost_equal(const Car& first, const Car& second)const;
		bool year_equal(const Car& first, const Car& second)const;
		bool power_equal(const Car& first, const Car& second)const;
	private:
		static const unsigned SELLER_MENU_SIZE = 5;
		enum { SORT_OPTIONS = 4, FIND_OPTIONS };
		enum { NAME = 1, COST, YEAR, POWER, EQUAL };
		const char* const seller_menu[SELLER_MENU_SIZE] =
		{ "By name","By cost","By year","By power","By car" };
	private:
		Compare compare[SORT_OPTIONS];
		Find find[FIND_OPTIONS];
		unsigned to_compare;
		unsigned to_find;
		Car car_to_search;
	};

	class AutoShop
	{
	public:
		AutoShop(size_t size, Plant car_gen);
		AutoShop() {}
		AutoShop(const AutoShop& shop) = default;
		AutoShop(AutoShop&& shop) = default;
		AutoShop& operator=(const AutoShop& shop) = default;
		AutoShop& operator=(AutoShop&& shop) = default;
		~AutoShop() {}
	public:
		void take_request();
		void fulfill_request();
		void propose_catalog()const;
		bool customer_is_out()const;
	private:
		void show()const;
		void sort();
		void stock();
		void sell();
		void find();
	private:
		enum { NO, YES };
		enum {
			QUIT, ADD, POP,
			SHOW, SORT, FIND
		};
		static const unsigned SHOP_MENU_SIZE = 5;
		const char* const shop_menu[SHOP_MENU_SIZE] =
		{ "Add","Sell","Show","Sort","Find" };
	private:
		unsigned request;
		Park cars;
		Seller seller;
	};
}
#endif