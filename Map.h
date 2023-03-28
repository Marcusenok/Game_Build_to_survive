#include <SFML/Graphics.hpp>
#include"Manager.h"
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

public:
	static Map* GetInstance();
	void DrawMap(sf::RenderWindow& window);
	void Create_new_bilding(sf::RenderWindow& window);
	int Chose_bild(sf::RenderWindow& window);
	bool Can_buld_sawmill(int x, int y);
};
