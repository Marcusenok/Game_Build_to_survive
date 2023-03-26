#include "Bild_new.h"

Bild_new::Bild_new(vector<string> _map_vector)
{
	map_vector = _map_vector;
}

void Bild_new::Draw_house(sf::RenderWindow& window, Manager* MGR)
{
	while (true) {
		Texture map;//текстура карты
		map.loadFromFile("image/map.png");//заряжаем текстуру картинкой
		Sprite s_map;//создаём спрайт для карты
		s_map.setTexture(map);//заливаем текстуру спрайтом

		Texture press_close;//текстура карты
		press_close.loadFromFile("image/interface/close.png");//заряжаем текстуру картинкой
		Sprite s_press_close;//создаём спрайт для карты
		s_press_close.setTexture(press_close);//заливаем текстуру спрайтом

		int coord_x = 0, coord_y = 0;
		bool create_new_bild = true;
		while (create_new_bild)
		{
			window.clear();

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
			for (int i = 1; i < 4; i++)
			{
				for (int j = 1; j < 4; j++)
				{
					if (coord_x == -2 || coord_y == -2 || coord_x == map_vector[0].length() - 3 || coord_y == map_vector.size() - 3
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '-'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == '1'
						|| map_vector[(coord_y * 32 + (j * 32)) / 32][(coord_x * 32 + (i * 32)) / 32] == 'l')
					{
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
			window.draw(s_press_close);
			window.display();
		}
	}
}
