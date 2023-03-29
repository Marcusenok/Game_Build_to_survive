#include"MSG.h"
#include"Bilding.h"
#include<list>

class Manager
{
private:
	static Manager* instance;

	std::list<Bilding*> objs;
	std::list<MSG*> msgs;
	Manager();
	Manager(const Manager&);
	~Manager();
	int wood = 300;
	int raw_food = 200;
	int fresh_food = 200;
	int people = 100;

public:
	static Manager* GetInstance();
	static void Destroy();

	void Update(float dt);
	void SendMsg(MSG* m);
	void DrawObjects(sf::RenderWindow& win);
};
