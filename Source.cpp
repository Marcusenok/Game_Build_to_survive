#include"Map.h"


int main()
{
	RenderWindow window(sf::VideoMode(1216, 928), "BUILD TO SURVIVE");
	window.setPosition(sf::Vector2i(300, 100));

	Manager* MGR = Manager::GetInstance();
	Map* MAP = Map::GetInstance();
	Resource_manager* RES_MGR = Resource_manager::GetInstance();

	Clock clock;
	clock.restart();
	float timer = 22;
	int days = 0;
	int hour = 0;

	while (window.isOpen())
	{
		timer += clock.restart().asSeconds();
		hour = int(timer) % 24;
		if (int(timer) / 24 > days) days += 1;
		cout << days << "--" << hour << endl;
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
					cout << sf::Mouse::getPosition(window).x << endl;
					cout << sf::Mouse::getPosition(window).y << endl;
					if (event.mouseButton.x >= 1152 && event.mouseButton.y <= 64)
					{
						MAP->Create_new_bilding(window);
					}
				}
			}
		}

		window.clear();

		MGR->Update(clock.restart().asSeconds());

		MAP->DrawMap(window);
		MGR->DrawObjects(window);
		window.display();
	}

	return 0;
}