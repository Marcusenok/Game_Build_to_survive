#include "Sawmill.h"

Sawmill::Sawmill(sf::Vector2<int> _position, int _level) :
	Bilding(_position, _level, LoadTexture("image\\house\\sawmill.png", { 0, 0, 96, 96 }))
{
}
