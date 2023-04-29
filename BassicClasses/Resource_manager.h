#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;


class Resource_manager
{
private:
	static Resource_manager* instance;

	int wood = 150;
	int raw_food = 100;
	int fresh_food = 50;
	int people = 100;
	int moral_spirit = 90;
	int count_Sawmill = 0;
	int count_HunterHouse = 0;
	int count_Kitchen = 0;
	int count_Hospital = 0;
	int homeless_people = people;
	int hungry_people = 0;

public:
	static Resource_manager* GetInstance();
	sf::Text GetText(int x, int y, string text, int text_size);
	sf::Texture* LoadTexture(const char* filename, const sf::IntRect& src_box);
	sf::Sprite* GetSprite(sf::Texture* texture, int x, int y);
	void SetWood(int _wood);
	void SetRaw_food(int _raw_food);
	void SetFresh_food(int _fresh_food);
	void SetMoral_spirit(int _moral_spirit);
	void SetHomeless_people(int _homeless_people);
	int GetWood();
	int GetRaw_food();
	int GetFresh_food();
	int GetPeople();
	int GetHomeless_people();
	int GetHungry_people();
	int GetMoral_spirit();
	int GetCount_Hospital();
	void ResourceExtraction();
	bool CanBildHouse();
	bool CanBildSawmill();
	bool CanBildHunterHouse();
	bool CanBildKitchen();
	bool CanBildHospital();
	void SetCountSawmill(int _count_Sawmill);
	void SetCount_HunterHouse(int _count_HunterHouse);
	void SetCount_Kitchen(int _count_HunterKitchen);
	void SetCount_Hospital(int _count_Hospital);
	void Update_moral_spirit();
	void ManDead();
};

