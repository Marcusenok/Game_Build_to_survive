#include "Kitchen.h"

Kitchen::Kitchen(sf::Vector2<int> _position, int _level) :
	Bilding(_position, _level, LoadTexture("image\\house\\kitchen.png", { 0, 0, 128, 128 }))
{
}