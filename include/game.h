#pragma once
#include "pch.h"
#include "game_data.h"

class Sigma::Game {
	private:
		//ТЕКСТУРЫ
		sf::Texture plus_texture;				//текстура +
		sf::Texture flask_textures[3];			//текстура колб
		sf::Texture main_texture;				//основная текстурка
		sf::Texture backg_texture;				//текстура фона
		sf::Texture client_textures[5];			//текстуры клиентов
		sf::Texture element_textures[5];		//текстуры элементов
		sf::Texture element_hover_textures[5];	//текстуры элементов при наводке
		sf::Texture icon_textures[5];			//текстуры иконов
		sf::Texture tigel_texture;				//тектура тигеля

		//СПРАЙТЫ
		sf::Sprite flask_sprites[3];			//спрайты колб
		sf::Sprite main_sprite;					//основной спрайт
		sf::Sprite backg_sprite;				//спрайт фона
		sf::Sprite client_sprites[5];			//спрайты клиентов
		sf::Sprite element_sprites[5];			//спрайты элементов
		sf::Sprite element_hover_sprites[5];	//спрайты элементов при наводке
		sf::Sprite icon_sprites[5];				//спрайты мини элементов
		sf::Sprite tigel_sprite;				//спрайт тигеля
		sf::Sprite HoveredSprite;				//активный спрайт

		sf::Mouse mouse;						//Мышь
		sf::Font font;							//Основной шрифт

		//Звук ходьбы
		sf::SoundBuffer walking_sb;
		sf::Sound walking_s;
		sf::Clock walk_clock;

		//Звук добавления элемента в тигель
		sf::SoundBuffer splash_sb;
		sf::Sound splash_s;

		//Звук наполнения колбы
		sf::SoundBuffer filling_the_flask_sb;
		sf::Sound filling_the_flask_s;

		//Звук оплаты клиента
		sf::SoundBuffer money_for_order_sb;
		sf::Sound money_for_order_s;

		//Звук подбора денег
		sf::SoundBuffer take_the_money_sb;
		sf::Sound take_the_money_s;





		//Деньги
		sf::Texture money_texture;
		sf::Sprite money_sprite;
		bool money = false;
		uint64_t money_count = 0;


		//тайм бар
		sf::RectangleShape time_bar_hover;
		sf::RectangleShape time_bar;

		//Элементы в тигеле (массив спрайтов иконок)
		std::vector<sf::Sprite> elements_in_tigel;
		//Счетчик каждого элемента в тигеле (для проверки заказа)
		uint16_t tigel_counter[5] = { 0, 0, 0, 0, 0 };

		//Проверка активности спрайта
		bool isHovered(const sf::Sprite& sprite);
		bool hover;
		
		//скорость клиента
		float client_speed = 0.9f;

		//время ожидания в мс
		uint64_t wait_time = 20000;

		//структура рецепта, страницы рецептов, книги рецептов
		struct Recipe {
			std::string name;
			std::vector<sf::Sprite> elements; //спрайты элементов
			uint16_t counter[5] = { 0, 0, 0, 0, 0 }; //счетчик каждого элемента в тигеле

		};

		struct RecipePage
		{
			uint16_t max_on_page = 4; 
			std::vector<Recipe> recipes;
		};

		struct RecipesBook {
			sf::Text text[4]; //текст рецепта
			sf::Sprite plus[4][4]; //спрайты плюсиков+
			uint16_t page_num = 0; //номер текущей страницы

			std::vector<RecipePage> pages;
			std::vector<Recipe> recipes_list;
		};

		//структура клиента
		struct Client {
			int recipe_num = 0;		//номер рецепта
			int client_type = 0;	//тип клиент (цвет)
			int flask_type = 0;		//тип колбы (зелья)
			bool waiting = false;	//ождиание
			bool finished = false;	//закончено
			sf::Clock clock;
		};
		
		sf::Text client_text;  //текст заказа
		sf::Text balance_text; //текст счета

		//Области для смены страниц
		sf::IntRect prev = sf::IntRect(298, 114, 50, 200); 
		sf::IntRect next = sf::IntRect(510, 114, 100, 200);

		//Таймер паузы (для реализации паузы в игре)
		sf::Clock pause_clock;
		uint64_t pause_elapsed = 0;






		sf::RenderWindow* m_window = nullptr;
		GameData* m_data = nullptr;		//игровые данные
		Client* current = nullptr;		//клиент
		RecipesBook recipe_book;
		bool* m_pause;					//пауза


		void update_balance(); 
		void new_client();
		void finish_the_order( int i);
		bool load_recipes();
		void update_recipe_book();
		void draw_recipe_book();
		void prev_page();
		void next_page();
		

	public:
		Game(sf::RenderWindow* window, GameData* data, bool* pause);
		void on_mouse_click(); 
		void on_keyboard(const sf::Event & event);
		bool load_data();
		void render();
		void update();

};
