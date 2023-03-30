#include "Resource_manager.h"

Font FONT;

Resource_manager* Resource_manager::instance = nullptr;

Resource_manager* Resource_manager::GetInstance()
{
	if (!instance)
	{
		instance = new Resource_manager();
	}
	return instance;
}

sf::Text Resource_manager::GetText(int x, int y, string text, int text_size)
{
	FONT.loadFromFile("ofont.ru_Arial Cyr.ttf");
	Text _text(text, FONT, text_size);
	_text.setFillColor(Color::White);
	_text.setPosition(x, y);
	return _text;
}

sf::Texture* Resource_manager::LoadTexture(const char* filename, const sf::IntRect& src_box)
{
	Texture* tex = new Texture();
	if (tex->loadFromFile(filename, src_box))
		return tex;
	delete tex;
	return nullptr;
}

sf::Sprite* Resource_manager::GetSprite(sf::Texture* texture, int x, int y)
{
	Sprite* sprite = new Sprite();
	sprite->setTexture(*texture);
	sprite->setPosition(x, y);
	return sprite;
}

void Resource_manager::SetWood(int _wood) { wood = _wood; }
void Resource_manager::SetRaw_food(int _raw_food) { raw_food = _raw_food; }
void Resource_manager::SetFresh_food(int _fresh_food) { fresh_food = _fresh_food; }
int Resource_manager::GetWood() { return wood; }
int Resource_manager::GetRaw_food() { return raw_food; }
int Resource_manager::GetFresh_food() { return fresh_food; }
int Resource_manager::GetPeople() { return people; }
void Resource_manager::ResourceExtraction() 
{
	wood += 5;
	raw_food += 10;
	fresh_food += 10;
}
