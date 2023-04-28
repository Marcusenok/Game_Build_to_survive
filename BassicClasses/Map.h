#include <SFML/Graphics.hpp>
#include"Manager.h"
#include"Resource_manager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace sf;
using namespace std;


class Map
{
private:
	static Map* instance;
	std::vector<string> map_vector;
	Manager* MGR = nullptr;
	Resource_manager* RES_MGR = nullptr;
	int _timer = 24;

public:
	static Map* GetInstance();
	void SetMap(const char* filename);
	void DrawMap(sf::RenderWindow& window, int days, float timer);
	void DrawMenu(sf::RenderWindow& window);
	void DrawSickPeople(sf::RenderWindow& window);
	void Pause(sf::RenderWindow& window, int days,int timer);
	void Create_new_bilding(sf::RenderWindow& window, int days, float timer);
	int Chose_bild(sf::RenderWindow& window);
	bool Can_buld_sawmill(int x, int y);
	void SetTime(int _timer);
	int GetTime();
	void EndGame(sf::RenderWindow& window);
	void GetSickPeople();
	void GetDeadPeople();
	void DeleteSickPeople(int x, int y);
};
