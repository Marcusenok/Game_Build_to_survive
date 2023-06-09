#include "./BassicClasses/Map.h"

int main()
{
	RenderWindow window(sf::VideoMode(1216, 928), "BUILD TO SURVIVE");
	window.setPosition(sf::Vector2i(300, 50));

	Manager* MGR = Manager::GetInstance();
	Map* MAP = Map::GetInstance();
	Resource_manager* RES_MGR = Resource_manager::GetInstance();

	MAP->DrawMenu(window);

	float timer = 24;
	timer = MAP->GetTime();
	int days = timer / 24;
	int get_resorse = 0;
	int get_hill = 0;
	int count_spped = 1;

	Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		timer += clock.restart().asSeconds() * count_spped;
		if (int(timer) / 24 > days)
		{
			days += 1;
			get_resorse = 0;
			get_hill = 0;
			RES_MGR->Update_moral_spirit();
			MAP->GetDeadPeople();
		}
		if (int(timer) % 24 == 12 && get_resorse == 0
			|| int(timer) % 24 == 16 && get_resorse == 1
			|| int(timer) % 24 == 20 && get_resorse == 2)
		{
			RES_MGR->ResourceExtraction();
			get_resorse = get_resorse + 1;
		}
		if (int(timer) % 24 == 0 && get_hill == 0 || int(timer) % 24 == 2 && get_hill == 1
			|| int(timer) % 24 == 4 && get_hill == 2 || int(timer) % 24 == 8 && get_hill == 3
			|| int(timer) % 24 == 12 && get_hill == 4 || int(timer) % 24 == 15 && get_hill == 5)
		{
			get_hill += 1;
			MAP->GetSickPeople();
		}
		if (RES_MGR->GetMoral_spirit() == 0) MAP->EndGame(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::Resized)
			{
				window.setSize(sf::Vector2u(1216, 928));
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 1024 && event.mouseButton.y >= 0
						&& event.mouseButton.x <= 1088 && event.mouseButton.y <= 64 && count_spped != 1) count_spped -= 1;
					if (event.mouseButton.x >= 1088 && event.mouseButton.y >= 0
						&& event.mouseButton.x <= 1152 && event.mouseButton.y <= 64 && count_spped != 4) count_spped += 1;
					if (event.mouseButton.x >= 960 && event.mouseButton.y >= 0
						&& event.mouseButton.x <= 1024 && event.mouseButton.y <= 64) MAP->Pause(window, days, timer);
					if (event.mouseButton.x >= 1152 && event.mouseButton.y <= 64)
					{
						MAP->Create_new_bilding(window, days, timer);
					}
					MAP->DeleteSickPeople(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
				}
			}
		}

		window.clear();

		MGR->Update(clock.restart().asSeconds());

		MAP->DrawMap(window, days, timer);
		MGR->DrawObjects(window);
		MAP->DrawSickPeople(window);

		window.display();
	}

	return 0;
}