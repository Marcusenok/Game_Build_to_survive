#ifndef AAA_BILDING
#define AAA_BILDING

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Bilding
{
protected:
	int level;
	int cost;

	sf::Texture* texture;
	sf::Vector2<int> position;
	sf::Sprite sprite;

	sf::Texture* LoadTexture(const char* filename, const sf::IntRect& src_box);

public:
	Bilding(sf::Vector2<int> position, int level, int cost, sf::Texture* texture);
	void Draw(sf::RenderWindow& window);
};


#endif
