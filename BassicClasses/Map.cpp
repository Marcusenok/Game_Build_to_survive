#include "Map.h"

Map* Map::instance = nullptr;

Map* Map::GetInstance()
{
	if (!instance)
	{
		instance = new Map();
		instance->MGR = Manager::GetInstance();
		instance->RES_MGR = Resource_manager::GetInstance();
	}
	return instance;
}

void Map::SetMap(const char* filename)
{
	string line;
	vector <string> _map_vector;
	ifstream file(filename);

	while (getline(file, line)) {
		_map_vector.push_back(line);
	}
	instance->map_vector = _map_vector;

	MSG* msg = new MSG;

	for (int i = 0; i < map_vector.size() - 4; i++)
	{
		for (int j = 0; j < map_vector[0].length(); j++)
		{
			if (map_vector[i][j] == '1')
			{
				RES_MGR->SetHomeless_people(RES_MGR->GetHomeless_people() - 5);
				msg = new MSG;
				msg->type = MsgType::Create;
				House* a = new House({ j * 32, i * 32 }, 1, 5);
				msg->create.new_object = a;
				instance->MGR->SendMsg(msg);
			}
			if (map_vector[i][j] == '2')
			{
				RES_MGR->SetCountSawmill(1);
				msg = new MSG;
				msg->type = MsgType::Create;
				Sawmill* a = new Sawmill({ j * 32, i * 32 }, 1);
				msg->create.new_object = a;
				instance->MGR->SendMsg(msg);
			}
			if (map_vector[i][j] == '3')
			{
				RES_MGR->SetCount_HunterHouse(1);
				MSG* msg = new MSG;
				msg->type = MsgType::Create;
				HuntersHouse* a = new HuntersHouse({ j * 32, i * 32 }, 1);
				msg->create.new_object = a;
				instance->MGR->SendMsg(msg);
			}
			if (map_vector[i][j] == '4')
			{
				RES_MGR->SetCount_Kitchen(1);
				MSG* msg = new MSG;
				msg->type = MsgType::Create;
				Kitchen* a = new Kitchen({ j * 32, i * 32 }, 1);
				msg->create.new_object = a;
				instance->MGR->SendMsg(msg);
			}
			if (map_vector[i][j] == '5')
			{
				RES_MGR->SetCount_Hospital(1);
				MSG* msg = new MSG;
				msg->type = MsgType::Create;
				Hospital* a = new Hospital({ j * 32, i * 32 }, 1);
				msg->create.new_object = a;
				instance->MGR->SendMsg(msg);
			}
		}
	}
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
	time_status_days.setString(L"ƒень " + to_string(days));
	Text time_status_hours = RES_MGR->GetText(0, 30, "", 30);
	time_status_hours.setString(L"¬рем€ " + to_string(int(timer) % 24));
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

void Map::DrawSickPeople(sf::RenderWindow& window)
{
	Texture* map = RES_MGR->LoadTexture("image/map.png", { 0, 0, 512 , 32 });
	Sprite s_map = *RES_MGR->GetSprite(map, 0, 0);;

	for (int i = 0; i < map_vector.size(); i++)
	{
		for (int j = 0; j < map_vector[0].length(); j++)
		{
			if (map_vector[i][j] == 's')
			{
				s_map.setTextureRect(IntRect(128, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
			if (map_vector[i][j] == 'd')
			{
				s_map.setTextureRect(IntRect(128, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		}
	}

	delete map;
}

void Map::SetTime(int timer)
{
	if (timer != 24)
	{
		_timer = timer;
	}
}

int Map::GetTime()
{
	return _timer;
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
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 303) 
					{
						SetMap("./MapAndSave/map_save.txt"); 
						in_menu = false;
						string line_resourse;
						vector <string> resourse_vector;
						ifstream file1("./MapAndSave/save_resourse.txt");

						while (getline(file1, line_resourse)) {
							resourse_vector.push_back(line_resourse);
						}

						RES_MGR->SetWood(stoi(resourse_vector[0]));
						RES_MGR->SetRaw_food(stoi(resourse_vector[1]));
						RES_MGR->SetFresh_food(stoi(resourse_vector[2]));
						RES_MGR->SetMoral_spirit(stoi(resourse_vector[3]));
						int	_timer = 24;
						_timer = stoi(resourse_vector[4]);
						SetTime(_timer);
					}
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 329
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 404) {
						SetMap("./MapAndSave/map.txt");
						in_menu = false;
					}
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 430
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 506) 
					{
						Texture* tutorial = RES_MGR->LoadTexture("image/interface/tutorial.png", { 0, 0, 1216, 928 });
						Sprite* s_tutorial = RES_MGR->GetSprite(tutorial, 0, 0);
						bool in_tutorial = true;
						while (in_tutorial)
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
										if (event.mouseButton.x >= 360 && event.mouseButton.y >= 852
											&& event.mouseButton.x <= 881 && event.mouseButton.y <= 909) in_tutorial = false;
									}
								}
							}
							window.draw(*s_tutorial);
							window.display();
						}
						delete tutorial;
					}
					if (event.mouseButton.x >= 360 && event.mouseButton.y >= 533
						&& event.mouseButton.x <= 855 && event.mouseButton.y <= 607) 
					{
						Texture* aboute_me = RES_MGR->LoadTexture("image/interface/aboute_me.png", { 0, 0, 1216, 928 });
						Sprite* s_aboute_me = RES_MGR->GetSprite(aboute_me, 0, 0);
						bool in_aboute_me = true;
						while (in_aboute_me)
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
									if (event.mouseButton.button == sf::Mouse::Left) in_aboute_me = false;
								}
							}
							window.draw(*s_aboute_me);
							window.display();
						}
						delete aboute_me;
					}
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

void Map::Pause(sf::RenderWindow& window, int days, int timer)
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
					if (event.mouseButton.x >= 422 && event.mouseButton.y >= 541
						&& event.mouseButton.x <= 812 && event.mouseButton.y <= 587)
					{
						std::ofstream out_map;
						out_map.open("./MapAndSave/map_save.txt");
						for (int i = 0; i < map_vector.size(); i++)
						{
							out_map << map_vector[i] << endl;
						}
						out_map.close();

						std::ofstream out_resourse;
						out_resourse.open("./MapAndSave/save_resourse.txt");
						out_resourse << RES_MGR->GetWood() << endl;
						out_resourse << RES_MGR->GetRaw_food() << endl;
						out_resourse << RES_MGR->GetFresh_food() << endl;
						out_resourse << RES_MGR->GetMoral_spirit() << endl;
						out_resourse << timer;
						out_resourse.close();
						exit(0);
					}
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

	Texture map;//текстура карты
	map.loadFromFile("image/map.png");//зар€жаем текстуру картинкой
	Sprite s_map;//создаЄм спрайт дл€ карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

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
								map_vector[coord_y + 1][coord_x + 1] = *"1";
								for (int i = 0; i <= 2; i++)
								{
									for(int j = 0; j <= 2; j++) if (map_vector[coord_y + 1 + i][coord_x + 1 + j] != *"1") map_vector[coord_y + 1 + i][coord_x + 1 + j] = *"-";
								}
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
									map_vector[coord_y + 1][coord_x + 1] = *"2";
									for (int i = 0; i <= 2; i++)
									{
										for (int j = 0; j <= 2; j++) if (map_vector[coord_y + 1 + i][coord_x + 1 + j] != *"2") map_vector[coord_y + 1 + i][coord_x + 1 + j] = *"-";
									}
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
									map_vector[coord_y + 1][coord_x + 1] = *"3";
									for (int i = 0; i <= 2; i++)
									{
										for (int j = 0; j <= 2; j++) if (map_vector[coord_y + 1 + i][coord_x + 1 + j] != *"3") map_vector[coord_y + 1 + i][coord_x + 1 + j] = *"-";
									}
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
								map_vector[coord_y + 1][coord_x + 1] = *"4";
								for (int i = 0; i <= 3; i++)
								{
									for (int j = 0; j <= 3; j++) if (map_vector[coord_y + 1 + i][coord_x + 1 + j] != *"4") map_vector[coord_y + 1 + i][coord_x + 1 + j] = *"-";
								}
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
								map_vector[coord_y + 1][coord_x + 1] = *"5";
								for (int i = 0; i <= 3; i++)
								{
									for (int j = 0; j <= 4; j++) if (map_vector[coord_y + 1 + i][coord_x + 1 + j] != *"5") map_vector[coord_y + 1 + i][coord_x + 1 + j] = *"-";
								}
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
		if (number_buld == 4) { idex_for_bilding_y += 1; idex_for_bilding_x += 1; };
		if (number_buld == 5) { idex_for_bilding_y += 2; idex_for_bilding_x += 1; };
		can_buld = true;
		if (number_buld != 0) {
			for (int i = 1; i < 4 + idex_for_bilding_y; i++)
			{
				for (int j = 1; j < 4 + idex_for_bilding_x; j++)
				{
					if (coord_x == -2 || coord_y == -2 || coord_x >= map_vector[0].length() - 3 - idex_for_bilding_y || coord_y >= map_vector.size() - 3 - idex_for_bilding_x 
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '-'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '1'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '2'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '3'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '4'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '5'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == 's'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == 'w')
					{
						can_buld = false;
						s_map.setTextureRect(IntRect(0, 0, 32, 32));
					}
					else
					{
						s_map.setTextureRect(IntRect(32, 0, 32, 32));
					}
					s_map.setPosition((coord_x * 32 + (	i * 32)), (coord_y * 32 + (j * 32)));
					window.draw(s_map);
				}
			}
		}

		if (number_buld == 2 or number_buld == 3)
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
	Texture chose;//текстура карты
	chose.loadFromFile("image/interface/chose_bild_menu.png");//зар€жаем текстуру картинкой
	Sprite s_chose;//создаЄм спрайт дл€ карты
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

void Map::EndGame(sf::RenderWindow& window)
{
	Texture* end_game = RES_MGR->LoadTexture("image/interface/game_over.png", { 0, 0, 1216, 928 });
	Sprite* s_end_game = RES_MGR->GetSprite(end_game, 0, 0);
	bool in_end_game = true;
	while (in_end_game)
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
				if (event.mouseButton.button == sf::Mouse::Left) exit(0);;
			}
		}
		window.draw(*s_end_game);
		window.display();
	}
	delete end_game;
}

void Map::GetSickPeople()
{
	int number_house = (RES_MGR->GetPeople() - RES_MGR->GetHomeless_people()) / 5;
	bool sick_people = false;
	for (int i = 0; i < number_house; i++) {
		int num = rand() % 100;
		if (num <= 8)
		{
			sick_people = true;
			number_house = i;
			break;
		}
	}
	int number_house_for_sick = -1;
	bool have_sick_people = false;
	if (sick_people) {
		for (int i = 0; i < map_vector.size() - 4; i++)
		{
			for (int j = 0; j < map_vector[0].length(); j++)
			{
				if (map_vector[i][j] == '1') 
				{
					number_house_for_sick += 1;
					if (map_vector[i + 1][j + 1] != 's' and !have_sick_people and number_house_for_sick == number_house)
					{
						map_vector[i + 1][j + 1] = 's';
						have_sick_people = true;
					}
				}
			}
		}
	}
}

void Map::GetDeadPeople()
{
	for (int i = 0; i < map_vector.size(); i++)
	{
		for (int j = 0; j < map_vector[0].length(); j++)
		{
			if (map_vector[i][j] == 's')
			{
				map_vector[i][j] = '-';
				RES_MGR->SetMoral_spirit(RES_MGR->GetMoral_spirit() - 5);
				RES_MGR->ManDead();
			} 
		}
	}
}

void Map::DeleteSickPeople(int x, int y)
{
	if(map_vector[y / 32][x / 32] == 's') map_vector[y / 32][x / 32] = '-';
}
