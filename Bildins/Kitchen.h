#include "Bilding.h"

class Kitchen : public Bilding
{
protected:
	int efficiency = 5;

public:
	Kitchen(sf::Vector2<int> _position, int _level);
};

