#include "Bilding.h"

class Hospital : public Bilding
{
protected:
	int efficiency = 2;

public:
	Hospital(sf::Vector2<int> _position, int _level);
};

