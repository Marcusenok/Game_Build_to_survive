#pragma once
#include "Bilding.h"

class Sawmill : public Bilding
{
protected:
	int efficiency = 3;

public:
	Sawmill(sf::Vector2<int> _position, int _level, int _cost);
};

