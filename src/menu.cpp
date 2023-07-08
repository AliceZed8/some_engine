#include "menu.h"


Sigma::Menu::Menu(sf::RenderWindow * window, GameData * data, bool * pause): 
	m_window(window), m_data(data), m_pause(pause) {
	INFO("Constructing Menu");
	state = State::MAIN;
	prev_state = State::MAIN;
	load_data();
}

void Sigma::Menu::load_data() {
	INFO("Loading menu data");


	tutorial.loadFromFile("assets/tutorial.png");
	tutorial_sprite.setTexture(tutorial);
	tutorial_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);

	menu_background_texture.loadFromFile("assets/menu.png");
	menu_background_sprite.setTexture(menu_background_texture);
	menu_background_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);

	play_button_texture.loadFromFile("assets/buttons/button_start.png");
	play_button.setTexture(play_button_texture);
	play_button.setScale(0.7f, 0.7f);
	play_button.setPosition(150, 300);

	tutorial_button_texture.loadFromFile("assets/buttons/button_tutorial.png");
	tutorial_button.setTexture(tutorial_button_texture);
	tutorial_button.setScale(0.7f, 0.7f);
	tutorial_button.setPosition(150, 450);

	quit_button_texture.loadFromFile("assets/buttons/button_exit.png");
	quit_button.setTexture(quit_button_texture);
	quit_button.setScale(0.7f, 0.7f);
	quit_button.setPosition(150, 450);

}

//Рисуем менюшку
void Sigma::Menu::draw() {
	m_window->draw(menu_background_sprite);

	switch (state)
	{
	case Sigma::Menu::MAIN:
		m_window->draw(play_button);
		//m_window->draw(tutorial_button);
		m_window->draw(quit_button);
		break;
	case Sigma::Menu::PAUSE:
		//m_window->draw(tutorial_button);
		m_window->draw(quit_button);
		break;
	case Sigma::Menu::TUTORIAL:
		m_window->draw(tutorial_sprite);
		break;
	}

}

//Находится ли спрайт под мышкой
bool Sigma::Menu::isHovered(const sf::Sprite & sprite) {
	return sprite.getGlobalBounds().contains(mouse.getPosition(*m_window).x, mouse.getPosition(*m_window).y);
}


//Апдейт
void Sigma::Menu::update() {
	
}

//обработка нажатий
void Sigma::Menu::on_keyboard(sf::Event event) {

}


//Обработка клика мыши
void Sigma::Menu::on_mouse_click() {
	if (isHovered(play_button)) {
		*m_pause = false;
		state = State::PAUSE;
		play_button.setPosition(-300, 100);
		//tutorial_button.setPosition(150, 300);
		quit_button.setPosition(150, 450);
	}

	if (isHovered(quit_button)) {
		m_window->close();
	}

}