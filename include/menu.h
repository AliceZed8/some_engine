#pragma once
#include "pch.h"


class Sigma::Menu {
private:

	sf::Texture buttons;			//текстура с кнопками

	//кнопочки
	sf::Sprite play_button;
	sf::Sprite play_button_hover;

	sf::Sprite settings_button;
	sf::Sprite settings_button_hover;

	sf::Sprite quit_button;
	sf::Sprite quit_button_hover;

	int hovered_button;

	sf::RenderWindow* m_window;
	GameData* m_data;
	bool* m_pause;
	sf::Mouse mouse;

	void load_data();
	bool isHovered(const sf::Sprite& sprite);
	enum State {MAIN, PAUSE};
	State state;


public:
	Menu(sf::RenderWindow* window, GameData* data, bool * pause);
	void draw();
	void update();
	void on_mouse_click();

};
