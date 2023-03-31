#include "./BassicClasses/Map.h"

int main()
{
	RenderWindow window(sf::VideoMode(1216, 928), "BUILD TO SURVIVE");
	window.setPosition(sf::Vector2i(300, 50));

	Manager* MGR = Manager::GetInstance();
	Map* MAP = Map::GetInstance();
	Resource_manager* RES_MGR = Resource_manager::GetInstance();

	Clock clock;
	clock.restart();
	float timer = 24;
	int days = 1;
	int get_resorse = 0;
	int count_spped = 1;

	MAP->DrawMenu(window);

	while (window.isOpen())
	{
		timer += clock.restart().asSeconds() * count_spped;
		if (int(timer) / 24 > days) 
		{
			days += 1;
			get_resorse = 0;
			RES_MGR->Update_moral_spirit();
		}
		if (int(timer) % 24 == 12 && get_resorse == 0 
			|| int(timer) % 24 == 16 && get_resorse == 1
			|| int(timer) % 24 == 20 && get_resorse == 2)
		{
			RES_MGR->ResourceExtraction();
			get_resorse = get_resorse + 1;
		}
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
						&& event.mouseButton.x <= 1024 && event.mouseButton.y <= 64) MAP->Pause(window);
					cout << sf::Mouse::getPosition(window).x << endl;
					cout << sf::Mouse::getPosition(window).y << endl;
					if (event.mouseButton.x >= 1152 && event.mouseButton.y <= 64)
					{
						MAP->Create_new_bilding(window, days, timer);
					}
				}
			}
		}

		window.clear();

		MGR->Update(clock.restart().asSeconds());

		MAP->DrawMap(window, days, timer);
		MGR->DrawObjects(window);
		window.display();
	}

	return 0;
}