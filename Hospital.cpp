#include "Hospital.h"

Hospital::Hospital(sf::Vector2<int> _position, int _level) :
	Bilding(_position, _level, LoadTexture("image\\house\\hospital.png", { 0, 0, 160, 128 }))
{
}