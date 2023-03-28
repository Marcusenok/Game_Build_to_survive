#include "Map.h"

Map* Map::instance = nullptr;

Map* Map::GetInstance()
{
	if (!instance) 
	{
		instance = new Map();
		instance->MGR = Manager::GetInstance();
		string line;
		vector <string> _map_vector;
		ifstream file("map.txt");

		while (getline(file, line)) {
			_map_vector.push_back(line);
		}

		instance->map_vector = _map_vector;
		
		MSG* msg = new MSG;

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
					instance->MGR->SendMsg(msg);
				}
				if (_map_vector[i][j] == '2')
				{
					msg = new MSG;
					msg->type = MsgType::Create;
					Sawmill* a = new Sawmill({ j * 32, i * 32 }, 3, 4);
					msg->create.new_object = a;
					instance->MGR->SendMsg(msg);
				}
			}
		}
	}
	return instance;
}

void Map::DrawMap(sf::RenderWindow& window)
{
	Texture map;//текстура карты
	map.loadFromFile("image/map.png");//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Texture press_to_buld;//текстура карты
	press_to_buld.loadFromFile("image/interface/press_to_buld.png");//заряжаем текстуру картинкой
	Sprite s_press_to_buld;//создаём спрайт для карты
	s_press_to_buld.setTexture(press_to_buld);//заливаем текстуру спрайтом
	s_press_to_buld.setPosition(1152, 0);

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
			if (map_vector[i][j] == 'w')
			{
				s_map.setTextureRect(IntRect(96, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		}
	}

	window.draw(s_press_to_buld);
}

void Map::Create_new_bilding(sf::RenderWindow& window)
{
	int number_buld = this->Chose_bild(window);
	Texture press_close;//текстура карты
	press_close.loadFromFile("image/interface/close.png");//заряжаем текстуру картинкой
	Sprite s_press_close;//создаём спрайт для карты
	s_press_close.setTexture(press_close);//заливаем текстуру спрайтом

	Texture map;//текстура карты
	map.loadFromFile("image/map.png");//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	int coord_x = sf::Mouse::getPosition(window).x / 32 - 2, coord_y = sf::Mouse::getPosition(window).y / 32 - 2;
	bool create_new_bild = true;
	bool can_buld = false;
	while (create_new_bild)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved)
			{
				coord_x = event.mouseMove.x / 32 - 2;
				coord_y = event.mouseMove.y / 32 - 2;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (can_buld)
					{
						switch (number_buld)
						{
							case 1:
							{
								MSG* msg = new MSG;
								msg->type = MsgType::Create;
								House* a = new House({ (coord_x + 1) * 32, (coord_y + 1) * 32 }, 3, 4, 5);
								msg->create.new_object = a;
								instance->MGR->SendMsg(msg);
								create_new_bild = false;
								break;
							}
							case 2:
							{
								if (Can_buld_sawmill(coord_x, coord_y))
								{
									MSG* msg = new MSG;
									msg->type = MsgType::Create;
									Sawmill* a = new Sawmill({ (coord_x + 1) * 32, (coord_y + 1) * 32 }, 3, 4);
									msg->create.new_object = a;
									instance->MGR->SendMsg(msg);
									create_new_bild = false;
								}
								break;
							}
							default:
								break;
						}
					}
				}
			}
		}

		window.clear();
		this->DrawMap(window);
		MGR->DrawObjects(window);

		can_buld = true;
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				if (coord_x == -2 || coord_y == -2 || coord_x == map_vector[0].length() - 3 || coord_y == map_vector.size() - 3
					|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '-'
					|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '1'
					|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '2'
					|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == 'w')
				{
					can_buld = false;
					s_map.setTextureRect(IntRect(0, 0, 32, 32));
				}
				else
				{
					s_map.setTextureRect(IntRect(32, 0, 32, 32));
				}
				s_map.setPosition((coord_x * 32 + (i * 32)), (coord_y * 32 + (j * 32)));
				window.draw(s_map);
			}
		}

		if (number_buld == 2)
		{
			if (Can_buld_sawmill(coord_x, coord_y) == false)
			{
				can_buld = false;
				s_map.setTextureRect(IntRect(0, 0, 32, 32));
				for (int i = 1; i < 4; i++)
				{
					for (int j = 1; j < 4; j++)
					{
						s_map.setPosition((coord_x * 32 + (i * 32)), (coord_y * 32 + (j * 32)));
						window.draw(s_map);
					}
				}
			}
		}

		window.draw(s_press_close);
		window.display();
	}
}


int Map::Chose_bild(sf::RenderWindow& window)
{
	int chose_number = 0;
	Texture chose;//текстура карты
	chose.loadFromFile("image/interface/chose_bild_menu.png");//заряжаем текстуру картинкой
	Sprite s_chose;//создаём спрайт для карты
	s_chose.setTexture(chose);//заливаем текстуру спрайтом
	s_chose.setPosition(150, 100);
	while (chose_number == 0)
	{
		window.draw(s_chose);
		window.display();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 406 && event.mouseButton.y >= 208
						&& event.mouseButton.x <= 794 && event.mouseButton.y <= 249)
						chose_number = 1;
					if (event.mouseButton.x >= 404 && event.mouseButton.y >= 288
						&& event.mouseButton.x <= 794 && event.mouseButton.y <= 331)
						chose_number = 2;

				}
			}
		}
	}
	return chose_number;
}

bool Map::Can_buld_sawmill(int x, int y)
{
	x += 2; y += 2;
	bool can_buld_sawmill = false;

	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			if ((0 <= x + i && x + i <= (map_vector[0].length() - 1)) && 0 <= j + y && j + y <= (map_vector.size() - 1))
			{
				if (map_vector[j + y][x + i] == 'w')
				{
					can_buld_sawmill = true;
					break;
				}
			}
		}
	}
	return can_buld_sawmill;
}


