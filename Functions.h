#pragma once

#ifndef FUNCT_H_
#define FUNCT_H_

#include "AutoShop.h"

Car rand_car();
Car defined_car();
int input(const char* msg, int up, int down);
void eatline();
bool err(int choice, int up, int down);
void pause(int seconds = 0);

#endif
