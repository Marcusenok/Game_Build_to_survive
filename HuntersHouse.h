#include "Bilding.h"

class HuntersHouse : public Bilding
{
protected:
	int efficiency = 5;

public:
	HuntersHouse(sf::Vector2<int> _position, int _level, int _cost);
};

