#pragma once
#include "pch.h"

class Sigma::Game {
	private:
		//Текстурки
		sf::Texture main_texture;				//основная текстурка
		sf::Texture backg_texture;				//текстура фона
		sf::Texture client_textures[5];			//текстуры клиентов
		sf::Texture element_textures[5];		//текстуры элементов
		sf::Texture element_hover_textures[5];	//текстуры элементов при наводке
		sf::Texture tigel_texture;				//тектура тигеля

		//Спрайты
		sf::Sprite main_sprite;					//основной спрайт
		sf::Sprite backg_sprite;				//спрайт фона
		sf::Sprite client_sprites[5];			//спрайты клиентов
		sf::Sprite element_sprites[5];			//спрайты элементов
		sf::Sprite element_hover_sprites[5];	//спрайты элементов при наводке
		sf::Sprite mini_element_sprites[5];		//спрайты мини элементов
		sf::Sprite tigel_sprite;				//спрайт тигеля

		sf::Sprite HoveredSprite;				//активный спрайт

		sf::Mouse mouse; 
		sf::Font font;							//Основной шрифт

		//Счетчик элементов в тигеле
		std::vector<sf::Sprite> elements_in_tigel;
		uint16_t t_count = 0;

		//Проверка активности спрайта
		bool isHovered(const sf::Sprite& sprite);
		bool hover;
		
		//скорость клиента
		float client_speed = 0.9f;

		//Класс клиента
		struct Client {
			int recipe_num = 0;
			int client_type = 0;
			bool waiting = false;
			bool finished = false;
			sf::Clock clock;
			Client() {
				srand(10000);
				client_type = rand() % 5;
				clock.restart();
			}
		};


		struct Recipe {

		};


		struct RecipesSlider {



		};

		//Таймер паузы (для реализации паузы в игре)
		sf::Clock pause_clock;
		uint64_t pause_elapsed = 0;

		sf::RenderWindow* m_window = nullptr;
		GameData* m_data = nullptr;		//игровые данные
		Client* current = nullptr;		//клиент
		bool* m_pause;					//пауза

		//тайм бар
		sf::RectangleShape time_bar_hover;
		sf::RectangleShape time_bar;


	public:
		Game(sf::RenderWindow* window, GameData* data, bool* pause);
		void on_mouse_click(); 
		void on_keyboard(const sf::Event & event);
		void load_data();
		void render();
		void update();

};
