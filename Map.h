#ifndef AAA_MAP
#define AAA_MAP

#include <iostream>
#include <fstream>
#include"Manager.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include"MSG.h"
#include"Sawmill.h"
using namespace sf;
using namespace std;

class Map
{
private:
	static Map* instance;
	std::vector<string> map_vector;

public:
	Map();
	static Map* GetInstance();
	void DrawMap(sf::RenderWindow& window);
};

#endif
