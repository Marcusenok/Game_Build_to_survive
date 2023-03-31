#include "Manager.h"
#include <algorithm>

using namespace std;

Manager* Manager::instance = nullptr;

Manager::Manager() : objs(), msgs()
{
}

Manager::Manager(const Manager&)
{
}

Manager::~Manager()
{
	for (auto x : objs)
	{
		delete x;
	}
	objs.clear();

	for (auto x : msgs)
	{
		delete x;
	}
	msgs.clear();
}

Manager* Manager::GetInstance()
{
	if (!instance) instance = new Manager();
	return instance;
}

void Manager::Destroy()
{
	if (instance) delete instance;
}

void Manager::Update(float dt)
{
	MSG* m;

	while (!msgs.empty())
	{
		m = msgs.front();
		msgs.pop_front();

		switch (m->type)
		{
			case MsgType::Create:
			{
				objs.push_back(m->create.new_object);
			}break;
		}
			
		delete m;
	}
}

void Manager::SendMsg(MSG* m)
{
	msgs.push_back(m);
}

void Manager::DrawObjects(sf::RenderWindow& win)
{
	for (auto obj : objs)
	{
		obj->Draw(win);
	}
}