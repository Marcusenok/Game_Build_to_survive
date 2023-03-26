#ifndef AAA_HOUSE
#define AAA_HOUSE

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class House
{
protected:
	int level;
	int cost;

	sf::Texture* texture;
	int x, y;
	sf::Sprite sprite;

	sf::Texture* LoadTexture(const char* filename, const sf::IntRect& src_box);

public:
	House(int x, int y, int level, int cost, sf::Texture* texture);
	void Draw(sf::RenderWindow& window);
};

#endif

