#pragma once

#ifndef AUTO_SHOP_H_
#define AUTO_SHOP_H_

#include <vector>
#include <iostream>
#include <string>
#include <array>

namespace shop
{
	class Seller;

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
		friend std::istream& operator >>
			(std::istream& is, Car& car);
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
		void find_menu()const;
		void sort_menu()const;
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
		void menu()const;
	private:
		enum { SORT_OPTIONS = 4, FIND_OPTIONS };
		enum { NAME = 1, COST, YEAR, POWER, EQUAL };
	private:
		std::array<Compare, SORT_OPTIONS> compare;
		std::array<Find, FIND_OPTIONS>find;
		unsigned to_compare;
		unsigned to_find;
		Car to_search;
	};

	class AutoShop
	{
		using Park = std::vector<Car>;
		using RandomCar = Car(*)();
	public:
		AutoShop(size_t size, RandomCar car);
		AutoShop() {}
		AutoShop(const AutoShop& shop) = default;
		AutoShop(AutoShop&& shop) = default;
		AutoShop& operator=(const AutoShop& shop) = default;
		AutoShop& operator=(AutoShop&& shop) = default;
		void take_request();
		void fulfill_request();
		void propose_catalog()const;
		bool customer_is_out()const;
		~AutoShop() {}
	private:
		void menu()const;
		void show(std::ostream& os)const;
		void sort();
		void stock();
		void sell();
		void find();
		Park find_cars()const;
	private:
		enum { NO, YES };
		enum {
			QUIT, ADD, POP,
			SHOW, SORT, FIND
		};
	private:
		unsigned request;
		Park cars;
		Seller seller;
	};
}
#endif