#pragma once
#include <iostream>
#include"Manager.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Bild_new
{
protected:
	vector <string> map_vector;

public:
	Bild_new(vector <string> _map_vector);
	void Draw_house(sf::RenderWindow& window, Manager* MGR);
};

