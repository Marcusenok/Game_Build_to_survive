#include "HuntersHouse.h"

HuntersHouse::HuntersHouse(sf::Vector2<int> _position, int _level) :
	Bilding(_position, _level, LoadTexture("image\\house\\hunters_house.png", { 0, 0, 96, 96 }))
{
}
