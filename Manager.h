#ifndef AAA_MANAGER
#define AAA_MANAGER

#include"MSG.h"
#include"House.h"
#include<list>

class Manager
{
private:
	static Manager* instance;

	std::list<House*> objs;
	std::list<MSG*> msgs;
	Manager();
	Manager(const Manager&);
	~Manager();

public:
	static Manager* GetInstance();
	static void Destroy();

	void Update(float dt);
	void SendMsg(MSG* m);
	void DrawObjects(sf::RenderWindow& win);
};

#endif

