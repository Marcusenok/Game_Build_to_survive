#include "Sawmill.h"

Sawmill::Sawmill(sf::Vector2<int> _position, int _level, int _cost) :
	Bilding(_position, _level, _cost, LoadTexture("image\\house\\sawmill.png", { 0, 0, 96, 96 }))
{
}
