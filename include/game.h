#pragma once
#include "pch.h"
#include "game_data.h"

class Sigma::Game {
	private:
		//��������
		sf::Texture plus_texture;				//�������� +
		sf::Texture flask_textures[3];			//�������� ����
		sf::Texture main_texture;				//�������� ���������
		sf::Texture backg_texture;				//�������� ����
		sf::Texture client_textures[5];			//�������� ��������
		sf::Texture element_textures[5];		//�������� ���������
		sf::Texture element_hover_textures[5];	//�������� ��������� ��� �������
		sf::Texture icon_textures[5];			//�������� ������
		sf::Texture tigel_texture;				//������� ������

		//�������
		sf::Sprite flask_sprites[3];			//������� ����
		sf::Sprite main_sprite;					//�������� ������
		sf::Sprite backg_sprite;				//������ ����
		sf::Sprite client_sprites[5];			//������� ��������
		sf::Sprite element_sprites[5];			//������� ���������
		sf::Sprite element_hover_sprites[5];	//������� ��������� ��� �������
		sf::Sprite icon_sprites[5];				//������� ���� ���������
		sf::Sprite tigel_sprite;				//������ ������
		sf::Sprite HoveredSprite;				//�������� ������

		sf::Mouse mouse;						//����
		sf::Font font;							//�������� �����

		//���� ������
		sf::SoundBuffer walking_sb;
		sf::Sound walking_s;
		sf::Clock walk_clock;

		//���� ���������� �������� � ������
		sf::SoundBuffer splash_sb;
		sf::Sound splash_s;

		//���� ���������� �����
		sf::SoundBuffer filling_the_flask_sb;
		sf::Sound filling_the_flask_s;

		//���� ������ �������
		sf::SoundBuffer money_for_order_sb;
		sf::Sound money_for_order_s;

		//���� ������� �����
		sf::SoundBuffer take_the_money_sb;
		sf::Sound take_the_money_s;





		//������
		sf::Texture money_texture;
		sf::Sprite money_sprite;
		bool money = false;
		uint64_t money_count = 0;


		//���� ���
		sf::RectangleShape time_bar_hover;
		sf::RectangleShape time_bar;

		//�������� � ������ (������ �������� ������)
		std::vector<sf::Sprite> elements_in_tigel;
		//������� ������� �������� � ������ (��� �������� ������)
		uint16_t tigel_counter[5] = { 0, 0, 0, 0, 0 };

		//�������� ���������� �������
		bool isHovered(const sf::Sprite& sprite);
		bool hover;
		
		//�������� �������
		float client_speed = 0.9f;

		//����� �������� � ��
		uint64_t wait_time = 20000;

		//��������� �������, �������� ��������, ����� ��������
		struct Recipe {
			std::string name;
			std::vector<sf::Sprite> elements; //������� ���������
			uint16_t counter[5] = { 0, 0, 0, 0, 0 }; //������� ������� �������� � ������

		};

		struct RecipePage
		{
			uint16_t max_on_page = 4; 
			std::vector<Recipe> recipes;
		};

		struct RecipesBook {
			sf::Text text[4]; //����� �������
			sf::Sprite plus[4][4]; //������� ��������+
			uint16_t page_num = 0; //����� ������� ��������

			std::vector<RecipePage> pages;
			std::vector<Recipe> recipes_list;
		};

		//��������� �������
		struct Client {
			int recipe_num = 0;		//����� �������
			int client_type = 0;	//��� ������ (����)
			int flask_type = 0;		//��� ����� (�����)
			bool waiting = false;	//��������
			bool finished = false;	//���������
			sf::Clock clock;
		};
		
		sf::Text client_text;  //����� ������
		sf::Text balance_text; //����� �����

		//������� ��� ����� �������
		sf::IntRect prev = sf::IntRect(298, 114, 50, 200); 
		sf::IntRect next = sf::IntRect(510, 114, 100, 200);

		//������ ����� (��� ���������� ����� � ����)
		sf::Clock pause_clock;
		uint64_t pause_elapsed = 0;






		sf::RenderWindow* m_window = nullptr;
		GameData* m_data = nullptr;		//������� ������
		Client* current = nullptr;		//������
		RecipesBook recipe_book;
		bool* m_pause;					//�����


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
