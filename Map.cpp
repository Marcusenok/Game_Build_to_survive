#include "Map.h"

Map* Map::instance = nullptr;

Map* Map::GetInstance()
{
	if (!instance) instance = new Map();
	return instance;
}

Map::Map()
{
	string line;
	vector <string> _map_vector;
	ifstream file("map.txt");

	while (getline(file, line)) {
		_map_vector.push_back(line);
	}

	map_vector = _map_vector;
}

void Map::DrawMap(sf::RenderWindow& window)
{
	Texture map;//текстура карты
	map.loadFromFile("image/map.png");//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	for (int i = 0; i < map_vector.size(); i++)
	{
		for (int j = 0; j < map_vector[0].length(); j++)
		{
			if (map_vector[i][j] == '0')
			{
				s_map.setTextureRect(IntRect(64, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
			if (map_vector[i][j] == 'l')
			{
				s_map.setTextureRect(IntRect(96, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		}
	}
}
