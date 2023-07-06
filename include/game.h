#pragma once
#include "pch.h"

class Sigma::Game {
	private:
		//���������
		sf::Texture main_texture;				//�������� ���������
		sf::Texture backg_texture;				//�������� ����
		sf::Texture client_textures[5];			//�������� ��������
		sf::Texture element_textures[5];		//�������� ���������
		sf::Texture element_hover_textures[5];	//�������� ��������� ��� �������
		sf::Texture tigel_texture;				//������� ������

		//�������
		sf::Sprite main_sprite;					//�������� ������
		sf::Sprite backg_sprite;				//������ ����
		sf::Sprite client_sprites[5];			//������� ��������
		sf::Sprite element_sprites[5];			//������� ���������
		sf::Sprite element_hover_sprites[5];	//������� ��������� ��� �������
		sf::Sprite mini_element_sprites[5];		//������� ���� ���������
		sf::Sprite tigel_sprite;				//������ ������

		sf::Sprite HoveredSprite;				//�������� ������

		sf::Mouse mouse; 
		sf::Font font;							//�������� �����

		//������� ��������� � ������
		std::vector<sf::Sprite> elements_in_tigel;
		uint16_t t_count = 0;

		//�������� ���������� �������
		bool isHovered(const sf::Sprite& sprite);
		bool hover;
		
		//�������� �������
		float client_speed = 0.9f;

		//����� �������
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

		//������ ����� (��� ���������� ����� � ����)
		sf::Clock pause_clock;
		uint64_t pause_elapsed = 0;

		sf::RenderWindow* m_window = nullptr;
		GameData* m_data = nullptr;		//������� ������
		Client* current = nullptr;		//������
		bool* m_pause;					//�����

		//���� ���
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
