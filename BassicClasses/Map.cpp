#include "Map.h"

Map* Map::instance = nullptr;

Map* Map::GetInstance()
{
	if (!instance) 
	{
		instance = new Map();
		instance->MGR = Manager::GetInstance();
		instance->RES_MGR = Resource_manager::GetInstance();
		string line;
		vector <string> _map_vector;
		ifstream file("./MapAndSave/map.txt");

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
					House* a = new House({ j * 32, i * 32 }, 1, 5);
					msg->create.new_object = a;
					instance->MGR->SendMsg(msg);
				}
				if (_map_vector[i][j] == '2')
				{
					msg = new MSG;
					msg->type = MsgType::Create;
					Sawmill* a = new Sawmill({ j * 32, i * 32 }, 1);
					msg->create.new_object = a;
					instance->MGR->SendMsg(msg);
				}
				if (_map_vector[i][j] == '3')
				{
					MSG* msg = new MSG;
					msg->type = MsgType::Create;
					HuntersHouse* a = new HuntersHouse({ j * 32, i * 32 }, 1);
					msg->create.new_object = a;
					instance->MGR->SendMsg(msg);
				}
				if (_map_vector[i][j] == '4')
				{
					MSG* msg = new MSG;
					msg->type = MsgType::Create;
					Kitchen* a = new Kitchen({ j * 32, i * 32 }, 1);
					msg->create.new_object = a;
					instance->MGR->SendMsg(msg);
				}
				if (_map_vector[i][j] == '5')
				{
					MSG* msg = new MSG;
					msg->type = MsgType::Create;
					Hospital* a = new Hospital({ j * 32, i * 32 }, 1);
					msg->create.new_object = a;
					instance->MGR->SendMsg(msg);
				}
			}
		}
	}
	return instance;
}

void Map::DrawMap(sf::RenderWindow& window, int days, float timer)
{
	Texture* map = RES_MGR->LoadTexture("image/map.png", { 0, 0, 512 , 32 });
	Sprite s_map = *RES_MGR->GetSprite(map, 0, 0);;

	Texture* press_to_buld = RES_MGR->LoadTexture("image/interface/press_to_buld.png", { 0, 0, 64, 64 });
	Sprite* s_press_to_buld = RES_MGR->GetSprite(press_to_buld, 1152, 0);
	Texture* press_to_sped_more = RES_MGR->LoadTexture("image/interface/spped_icon+.png", { 0, 0, 64, 64 });
	Sprite* s_press_to_sped_more = RES_MGR->GetSprite(press_to_sped_more, 1088, 0);
	Texture* press_to_sped_less = RES_MGR->LoadTexture("image/interface/spped_icon-.png", { 0, 0, 64, 64 });
	Sprite* s_press_to_sped_less = RES_MGR->GetSprite(press_to_sped_less, 1024, 0);
	Texture* press_to_pause = RES_MGR->LoadTexture("image/interface/pausa.png", { 0, 0, 64, 64 });
	Sprite* s_press_to_pause = RES_MGR->GetSprite(press_to_pause, 960, 0);
	Texture* moral_spirit = RES_MGR->LoadTexture("image/interface/moral_spirit.png", { 0, 0, 350, 55 });
	Sprite* s_moral_spirit = RES_MGR->GetSprite(moral_spirit, 433, 880);
	Texture* moral_spirit_completion = RES_MGR->LoadTexture("image/interface/moral_spirit_completion.png", { 0, 0, 320, 28 });
	Sprite s_moral_spirit_completion = *RES_MGR->GetSprite(moral_spirit_completion, 448, 893);
	Texture* info_about_people = RES_MGR->LoadTexture("image/interface/info_about_people.png", { 0, 0, 108, 120 });
	Sprite* s_info_about_people = RES_MGR->GetSprite(info_about_people, 0, 805);

	Texture* resourse_info = RES_MGR->LoadTexture("image/interface/resourse_info.png", { 0, 0, 600, 55 });
	Sprite* s_resourse_info = RES_MGR->GetSprite(resourse_info, 306, 0);

	Text time_status_days = RES_MGR->GetText(0, 5, "", 30);
	time_status_days.setString(L"���� " + to_string(days));
	Text time_status_hours = RES_MGR->GetText(0, 30, "", 30);
	time_status_hours.setString(L"����� " + to_string(int(timer) % 24));
	Text info_wood = RES_MGR->GetText(387, 5, to_string(RES_MGR->GetWood()), 25);
	Text raw_food = RES_MGR->GetText(519, 5, to_string(RES_MGR->GetRaw_food()), 25);
	Text fresh_food = RES_MGR->GetText(668, 5, to_string(RES_MGR->GetFresh_food()), 25);
	Text people = RES_MGR->GetText(799, 5, to_string(RES_MGR->GetPeople()), 25);
	Text homeless_people = RES_MGR->GetText(55, 818, to_string(RES_MGR->GetHomeless_people()), 25);
	Text hungry_people = RES_MGR->GetText(55, 868, to_string(RES_MGR->GetHungry_people()), 25);

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

	window.draw(*s_press_to_sped_more);
	window.draw(*s_press_to_sped_less);
	window.draw(*s_press_to_buld);
	window.draw(*s_press_to_pause);
	window.draw(*s_resourse_info);
	window.draw(*s_moral_spirit);
	window.draw(*s_info_about_people);
	window.draw(info_wood);
	window.draw(raw_food);
	window.draw(fresh_food);
	window.draw(people);
	window.draw(homeless_people);
	window.draw(hungry_people);
	window.draw(time_status_hours);
	window.draw(time_status_days);
	s_moral_spirit_completion.setTextureRect(IntRect(0, 0, RES_MGR->GetMoral_spirit() * 3.2, 28));
	window.draw(s_moral_spirit_completion);

	delete map;
	delete moral_spirit;
	delete press_to_buld;
	delete resourse_info;
	delete press_to_sped_more;
	delete press_to_sped_less;
	delete press_to_pause;
	delete moral_spirit_completion;
	delete info_about_people;
}

void Map::DrawMenu(sf::RenderWindow& window)
{
	bool in_menu = true;
	Texture* menu = RES_MGR->LoadTexture("image/interface/menu.png", { 0, 0, 1216, 928 });
	Sprite* s_menu = RES_MGR->GetSprite(menu, 0, 0);
	while (in_menu) 
	{
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
					cout << sf::Mouse::getPosition(window).x << " ";
					cout << sf::Mouse::getPosition(window).y << endl;
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 226
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 303) in_menu = false;
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 329
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 404) in_menu = false;
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 430
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 506) in_menu = false;
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 533
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 607) in_menu = false;
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 633
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 708) exit(0);
				}
			}
		}
		window.draw(*s_menu);
		window.display();
	}
	delete menu;
}

void Map::Pause(sf::RenderWindow& window)
{
	bool in_pause = true;
	Texture* menu_pause = RES_MGR->LoadTexture("image/interface/menu_pause.png", { 0, 0, 1216, 928 });
	Sprite* s_menu_pause = RES_MGR->GetSprite(menu_pause, 0, 0);
	while (in_pause)
	{
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
					in_pause = false;
				}
			}
		}
		window.draw(*s_menu_pause);
		window.display();
	}
	delete menu_pause;
}

void Map::Create_new_bilding(sf::RenderWindow& window, int days, float timer)
{
	int number_buld = this->Chose_bild(window);

	Texture map;//�������� �����
	map.loadFromFile("image/map.png");//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	int coord_x = sf::Mouse::getPosition(window).x / 32 - 2, coord_y = sf::Mouse::getPosition(window).y / 32 - 2;
	bool create_new_bild = true;
	bool can_buld = false;
	while (create_new_bild && number_buld != 0)
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
				if (event.mouseButton.button == sf::Mouse::Right) create_new_bild = false;
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (can_buld)
					{
						switch (number_buld)
						{
							case 1:
							{
								RES_MGR->SetWood(RES_MGR->GetWood() - 25);
								RES_MGR->SetHomeless_people(RES_MGR->GetHomeless_people() - 5);
								MSG* msg = new MSG;
								msg->type = MsgType::Create;
								House* a = new House({ (coord_x + 1) * 32, (coord_y + 1) * 32 }, 1, 5);
								msg->create.new_object = a;
								instance->MGR->SendMsg(msg);
								create_new_bild = false;
								break;
							}
							case 2:
							{
								if (Can_buld_sawmill(coord_x, coord_y))
								{
									RES_MGR->SetWood(RES_MGR->GetWood() - 20);
									RES_MGR->SetCountSawmill(1);
									MSG* msg = new MSG;
									msg->type = MsgType::Create;
									Sawmill* a = new Sawmill({ (coord_x + 1) * 32, (coord_y + 1) * 32 }, 1);
									msg->create.new_object = a;
									instance->MGR->SendMsg(msg);
									create_new_bild = false;
								}
								break;
							}
							case 3:
							{
								if (Can_buld_sawmill(coord_x, coord_y))
								{
									RES_MGR->SetWood(RES_MGR->GetWood() - 20);
									RES_MGR->SetCount_HunterHouse(1);
									MSG* msg = new MSG;
									msg->type = MsgType::Create;
									HuntersHouse* a = new HuntersHouse({ (coord_x + 1) * 32, (coord_y + 1) * 32 }, 1);
									msg->create.new_object = a;
									instance->MGR->SendMsg(msg);
									create_new_bild = false;
								}
								break;
							}
							case 4:
							{
								RES_MGR->SetWood(RES_MGR->GetWood() - 60);
								RES_MGR->SetCount_Kitchen(1);
								cout << number_buld;
								MSG* msg = new MSG;
								msg->type = MsgType::Create;
								Kitchen* a = new Kitchen({ (coord_x + 1) * 32, (coord_y + 1) * 32 }, 1);
								msg->create.new_object = a;
								instance->MGR->SendMsg(msg);
								create_new_bild = false;
								break;
							}
							case 5:
							{
								RES_MGR->SetWood(RES_MGR->GetWood() - 100);
								RES_MGR->SetCount_Hospital(1);
								MSG* msg = new MSG;
								msg->type = MsgType::Create;
								Hospital* a = new Hospital({ (coord_x + 1) * 32, (coord_y + 1) * 32 }, 1);
								msg->create.new_object = a;
								instance->MGR->SendMsg(msg);
								create_new_bild = false;
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
		this->DrawMap(window, days, timer);
		MGR->DrawObjects(window);
		int idex_for_bilding_x = 0, idex_for_bilding_y = 0;
		if (number_buld == 4) { idex_for_bilding_x += 1; idex_for_bilding_y += 1; };
		if (number_buld == 5) { idex_for_bilding_x += 2; idex_for_bilding_y += 1; };
		can_buld = true;
		if (number_buld != 0) {
			for (int i = 1; i < 4 + idex_for_bilding_x; i++)
			{
				for (int j = 1; j < 4 + idex_for_bilding_y; j++)
				{
					if (coord_x == -2 || coord_y == -2 || coord_x == map_vector[0].length() - 3 || coord_y == map_vector.size() - 3
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '-'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '1'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '2'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '3'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '4'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '5'
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
		window.display();
	}
}

int Map::Chose_bild(sf::RenderWindow& window)
{
	int chose_number = 0;
	Texture chose;//�������� �����
	chose.loadFromFile("image/interface/chose_bild_menu.png");//�������� �������� ���������
	Sprite s_chose;//������ ������ ��� �����
	s_chose.setTexture(chose);//�������� �������� ��������
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
				if (event.mouseButton.button == sf::Mouse::Right) return chose_number;
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					cout << sf::Mouse::getPosition(window).x << endl;
					cout << sf::Mouse::getPosition(window).y << endl;
					if (event.mouseButton.x >= 406 && event.mouseButton.y >= 208
						&& event.mouseButton.x <= 794 && event.mouseButton.y <= 249 && RES_MGR->CanBildHouse())
						chose_number = 1;
					if (event.mouseButton.x >= 404 && event.mouseButton.y >= 288
						&& event.mouseButton.x <= 794 && event.mouseButton.y <= 331 && RES_MGR->CanBildSawmill())
						chose_number = 2;
					if (event.mouseButton.x >= 414 && event.mouseButton.y >= 369
						&& event.mouseButton.x <= 806 && event.mouseButton.y <= 414 && RES_MGR->CanBildHunterHouse())
						chose_number = 3;
					if (event.mouseButton.x >= 416 && event.mouseButton.y >= 452
						&& event.mouseButton.x <= 807 && event.mouseButton.y <= 496 && RES_MGR->CanBildKitchen())
						chose_number = 4;
					if (event.mouseButton.x >= 417 && event.mouseButton.y >= 536
						&& event.mouseButton.x <= 808 && event.mouseButton.y <= 580 && RES_MGR->CanBildHospital())
						chose_number = 5;
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