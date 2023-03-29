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

Text Resource_manager::setString(int x, int y, string text)
{
	FONT.loadFromFile("ArefRuqaaInk-Regular.ttf");
	Text _text(text, FONT, 25);
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
	delete sprite;
}