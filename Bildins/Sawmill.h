#pragma once
#include "Bilding.h"

class Sawmill : public Bilding
{
protected:
	int efficiency = 5;

public:
	Sawmill(sf::Vector2<int> _position, int _level);
};

