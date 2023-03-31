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
void Resource_manager::SetHomeless_people(int _homeless_people) { if(homeless_people > 0) homeless_people = _homeless_people; }
int Resource_manager::GetWood() { return wood; }
int Resource_manager::GetRaw_food() { return raw_food; }
int Resource_manager::GetFresh_food() { return fresh_food; }
int Resource_manager::GetPeople() { return people; }
int Resource_manager::GetMoral_spirit(){ return moral_spirit; };
int Resource_manager::GetHomeless_people() { return homeless_people; };
int Resource_manager::GetHungry_people() { return hungry_people; };
void Resource_manager::SetCountSawmill(int _count_Sawmill) { count_Sawmill += _count_Sawmill; }
void Resource_manager::SetCount_HunterHouse(int _count_HunterHouse) { count_HunterHouse += _count_HunterHouse; }
void Resource_manager::SetCount_Kitchen(int _count_Kitchen) { count_Kitchen += _count_Kitchen; }
void Resource_manager::SetCount_Hospital(int _count_Hospital) { count_Hospital += _count_Hospital; }
void Resource_manager::SetMoral_spirit(int _moral_spirit) { moral_spirit = _moral_spirit; };

void Resource_manager::ResourceExtraction() 
{
	wood += 5 * count_Sawmill;
	raw_food += 5 * count_HunterHouse;
}

void Resource_manager::Update_moral_spirit()
{
	moral_spirit += people * 0.05;
	if (raw_food > 25 * count_Kitchen)
	{
		raw_food -= 25 * count_Kitchen;
		fresh_food += 50 * count_Kitchen;
	}
	if (fresh_food > people) fresh_food - people;
	else { 
		hungry_people = people - fresh_food;
		fresh_food = 0;
		if (moral_spirit - hungry_people * 0.2 < 0)moral_spirit = 0;
		else moral_spirit -= hungry_people * 0.2;
	}
	if (moral_spirit - homeless_people * 0.1 < 0) moral_spirit = 0;
	else moral_spirit -= homeless_people * 0.1;
	moral_spirit += 10 * count_Hospital;
	cout << moral_spirit;
}

bool Resource_manager::CanBildHouse()
{
	if (wood > 25) return true; 
	return false;
}
bool Resource_manager::CanBildSawmill() 
{
	if (wood > 20) return true;
	return false;
}
bool Resource_manager::CanBildHunterHouse() 
{
	if (wood > 20) return true;
	return false;
}
bool Resource_manager::CanBildKitchen() 
{
	if (wood > 60) return true;
	return false;
}
bool Resource_manager::CanBildHospital() 
{
	if (wood > 100) return true;
	return false;
}
