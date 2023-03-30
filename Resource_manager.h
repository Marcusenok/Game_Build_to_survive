#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;


class Resource_manager
{
private:
	static Resource_manager* instance;

	int wood = 300;
	int raw_food = 200;
	int fresh_food = 200;
	int people = 100;

public:
	static Resource_manager* GetInstance();
	sf::Text GetText(int x, int y, string text, int text_size);
	sf::Texture* LoadTexture(const char* filename, const sf::IntRect& src_box);
	sf::Sprite* GetSprite(sf::Texture* texture, int x, int y);
	void SetWood(int _wood);
	void SetRaw_food(int _raw_food);
	void SetFresh_food(int _fresh_food);
	int GetWood();
	int GetRaw_food();
	int GetFresh_food();
	int GetPeople();
	void ResourceExtraction();
};

