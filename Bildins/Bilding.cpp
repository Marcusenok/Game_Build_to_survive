#include "Bilding.h"

sf::Texture* Bilding::LoadTexture(const char* filename, const sf::IntRect& src_box)
{
    Texture* tex = new Texture();
    if (tex->loadFromFile(filename, src_box))
        return tex;
    delete tex;
    return nullptr;
}

Bilding::Bilding(sf::Vector2<int> _position, int _level, sf::Texture* _texture)
{   
    position = _position;
    level = _level;
    texture = _texture;
    sprite.setTexture(*texture);
}

void Bilding::Draw(sf::RenderWindow& window)
{
    sprite.setPosition(position.x, position.y);
    window.draw(sprite);
}
