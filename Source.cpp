#include <SFML/Graphics.hpp>
#include"House.h"
#include"MSG.h"
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
	Texture press_close;//�������� �����
	press_close.loadFromFile("image/interface/close.png");//�������� �������� ���������
	Sprite s_press_close;//������ ������ ��� �����
	s_press_close.setTexture(press_close);//�������� �������� ��������

	Texture map;//�������� �����
	map.loadFromFile("image/map.png");//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Texture chose;//�������� �����
	chose.loadFromFile("image/interface/chose.png");//�������� �������� ���������
	Sprite s_chose;//������ ������ ��� �����
	s_chose.setTexture(chose);//�������� �������� ��������
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

		/////////////////////////////������ �����/////////////////////
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

	Texture map;//�������� �����
	map.loadFromFile("image/map.png");//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Texture press_to_buld;//�������� �����
	press_to_buld.loadFromFile("image/interface/press_to_buld.png");//�������� �������� ���������
	Sprite s_press_to_buld;//������ ������ ��� �����
	s_press_to_buld.setTexture(press_to_buld);//�������� �������� ��������

	Texture house1;//�������� �����
	house1.loadFromFile("image/house/house_lvl1.png");//�������� �������� ���������
	Sprite s_house1;//������ ������ ��� �����
	s_house1.setTexture(house1);//�������� �������� ��������


	Manager* MGR = Manager::GetInstance();

	MSG* msg = new MSG;

	Clock clock;
	clock.restart();

	string line;
	vector <string> map_vector;
	ifstream file("map.txt");

	while (getline(file, line)) {
		map_vector.push_back(line);
	}

	for (int i = 0; i < map_vector.size(); i++)
	{
		for (int j = 0; j < map_vector[0].length(); j++)
		{
			if (map_vector[i][j] == '1') 
			{
				msg = new MSG;
				msg->type = MsgType::Create;
				House* a = new House(i*32, j*32, 3, 4, &house1);
				msg->create.new_object = a;
				MGR->SendMsg(msg);
			}
		}
	}


	while (window.isOpen())
	{
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
						buld_new(window, MGR, map_vector);
					}
				}
			}
		}

		window.clear();

		/////////////////////////////������ �����/////////////////////
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

		MGR->Update(clock.restart().asSeconds());

		MGR->DrawObjects(window);
		window.draw(s_press_to_buld);
		window.display();
	}

	return 0;
}