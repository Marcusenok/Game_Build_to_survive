#include "House.h"

House::House(sf::Vector2<int> _position, int _level, int _cost, int _capacity_people) :
    Bilding(_position, _level, _cost, LoadTexture("image\\house\\house_lvl1.png", { 0, 0, 96, 96 }))
{
    capacity_people = _capacity_people;
}
