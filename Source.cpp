#include"Map.h"


int main()
{
	RenderWindow window(sf::VideoMode(1216, 928), "BUILD TO SURVIVE");

	Manager* MGR = Manager::GetInstance();
	Map* MAP = Map::GetInstance();

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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
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