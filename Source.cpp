#include <SFML/Graphics.hpp>
#include"Bild_new.h"
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;


void buld_new(RenderWindow& window, Manager* MGR, vector <string> map_vector)
{
	Texture press_close;//текстура карты
	press_close.loadFromFile("image/interface/close.png");//заряжаем текстуру картинкой
	Sprite s_press_close;//создаём спрайт для карты
	s_press_close.setTexture(press_close);//заливаем текстуру спрайтом

	Texture map;//текстура карты
	map.loadFromFile("image/map.png");//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Texture chose;//текстура карты
	chose.loadFromFile("image/interface/chose.png");//заряжаем текстуру картинкой
	Sprite s_chose;//создаём спрайт для карты
	s_chose.setTexture(chose);//заливаем текстуру спрайтом
	s_chose.setPosition(420, 500);

	bool create_new_bild = true;
	while (create_new_bild)
	{
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x <= 64 && event.mouseButton.y <= 64)
					{
						Bild_new house(map_vector);
						house.Draw_house(window, MGR);
					}
				}
			}
		}

		/////////////////////////////Рисуем карту/////////////////////
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

		MGR->DrawObjects(window);
		window.draw(s_press_close);
		window.draw(s_chose);
		window.display();
	}
}

int main()
{
	RenderWindow window(sf::VideoMode(1216, 928), "BUILD TO SURVIVE");

	Texture map;//текстура карты
	map.loadFromFile("image/map.png");//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Texture press_to_buld;//текстура карты
	press_to_buld.loadFromFile("image/interface/press_to_buld.png");//заряжаем текстуру картинкой
	Sprite s_press_to_buld;//создаём спрайт для карты
	s_press_to_buld.setTexture(press_to_buld);//заливаем текстуру спрайтом


	Manager* MGR = Manager::GetInstance();
	Map* MAP = Map::GetInstance();

	MSG* msg = new MSG;

	string line;
	vector <string> _map_vector;
	ifstream file("map.txt");

	while (getline(file, line)) {
		_map_vector.push_back(line);
	}

	for (int i = 0; i < _map_vector.size(); i++)
	{
		for (int j = 0; j < _map_vector[0].length(); j++)
		{
			if (_map_vector[i][j] == '1')
			{
				msg = new MSG;
				msg->type = MsgType::Create;
				House* a = new House({ j * 32, i * 32 }, 3, 4, 5);
				msg->create.new_object = a;
				MGR->SendMsg(msg);
			}
			if (_map_vector[i][j] == 's')
			{
				msg = new MSG;
				msg->type = MsgType::Create;
				Sawmill* a = new Sawmill({ j * 32, i * 32 }, 3, 4);
				msg->create.new_object = a;
				MGR->SendMsg(msg);
			}
		}
	}

	Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		MGR->Update(clock.restart().asSeconds());

		MAP->DrawMap(window);
		MGR->DrawObjects(window);
		window.draw(s_press_to_buld);
		window.display();
	}

	return 0;
}