#pragma once
#include "pch.h"


class Sigma::Menu {
private:
	// фон
	sf::Texture menu_background_texture;
	sf::Sprite menu_background_sprite;

	// Туториал

	sf::Texture tutorial;
	sf::Sprite tutorial_sprite;


	//текстуры
	sf::Texture play_button_texture;	
	sf::Texture tutorial_button_texture;
	sf::Texture quit_button_texture;

	//кнопочки
	sf::Sprite play_button;
	sf::Sprite tutorial_button;
	sf::Sprite quit_button;

	sf::RenderWindow* m_window;
	GameData* m_data;
	bool* m_pause;
	sf::Mouse mouse;

	void load_data();
	bool isHovered(const sf::Sprite& sprite);
	enum State {MAIN, PAUSE, TUTORIAL};
	State state, prev_state;


public:
	Menu(sf::RenderWindow* window, GameData* data, bool * pause);
	void draw();
	void update();
	void on_keyboard(sf::Event event);
	void on_mouse_click();

};
