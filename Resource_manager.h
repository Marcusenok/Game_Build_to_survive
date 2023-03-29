#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;


class Resource_manager
{
private:
	static Resource_manager* instance;

public:
	int wood = 300;
	int raw_food = 200;
	int fresh_food = 200;
	int people = 100;

	static Resource_manager* GetInstance();
	sf::Text setString(int x, int y, string text);
	sf::Texture* LoadTexture(const char* filename, const sf::IntRect& src_box);
	sf::Sprite* GetSprite(sf::Texture* texture, int x, int y);
};

