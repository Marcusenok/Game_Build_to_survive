#include"Bilding.h"


class House : public Bilding
{
protected:
	int capacity_people;

public:
	House(sf::Vector2<int> _position, int _level, int _cost, int _capacity_people);
};

