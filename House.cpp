#include "House.h"

sf::Texture* House::LoadTexture(const char* filename, const sf::IntRect& src_box)
{
    Texture* tex = new Texture();
    if (tex->loadFromFile(filename, src_box))
        return tex;
    delete tex;
    return nullptr;
}

House::House(int _x, int _y, int _level, int _cost, sf::Texture* _texture)
{
    x = _x;
    y = _y;
    level = _level;
    texture = LoadTexture("image\\house\\house_lvl1.png", { 0, 0, 96, 96 });
    sprite.setTexture(*texture);
}

void House::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(y, x);
	window.draw(sprite);
}
