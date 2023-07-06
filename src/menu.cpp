#include "menu.h"


Sigma::Menu::Menu(sf::RenderWindow * window, GameData * data, bool * pause): 
	m_window(window), m_data(data), m_pause(pause) {
	INFO("Constructing Menu");
	state = State::MAIN;
	load_data();
}

void Sigma::Menu::load_data() {
	INFO("Loading menu data");

	buttons.loadFromFile("assets/buttons.png");

	//Загружаем спрайты
	play_button.setTexture(buttons);
	play_button.setTextureRect(sf::IntRect(0, 0, 222, 108)); //Вырезаем из текстуры область
	play_button.setScale(0.8f, 0.8f);
	play_button.setPosition(215, 390);

	play_button_hover.setTexture(buttons);
	play_button_hover.setTextureRect(sf::IntRect(223, 0, 221, 108));
	play_button_hover.setScale(0.8f, 0.8f);
	play_button_hover.setPosition(215, 390);

	
	settings_button.setTexture(buttons);
	settings_button.setTextureRect(sf::IntRect(0, 217, 222, 108));
	settings_button.setScale(0.8f, 0.8f);
	settings_button.setPosition(215, 475);

	settings_button_hover.setTexture(buttons);
	settings_button_hover.setTextureRect(sf::IntRect(223, 217, 221, 108));
	settings_button_hover.setScale(0.8f, 0.8f);
	settings_button_hover.setPosition(215, 475);


	quit_button.setTexture(buttons);
	quit_button.setTextureRect(sf::IntRect(0, 109, 222, 108));
	quit_button.setScale(0.8f, 0.8f);
	quit_button.setPosition(215, 560);

	quit_button_hover.setTexture(buttons);
	quit_button_hover.setTextureRect(sf::IntRect(223, 109, 221, 108));
	quit_button_hover.setScale(0.8f, 0.8f);
	quit_button_hover.setPosition(215, 560);

	//Размытый фон для меню
	main_blur.loadFromFile("assets/main_blur.png");
	main_blur_sprite.setTexture(main_blur);
}

//Рисуем менюшку
void Sigma::Menu::draw() {
	m_window->draw(main_blur_sprite);

	if (state == State::MAIN) {
		if (isHovered(play_button)) m_window->draw(play_button_hover);
		else m_window->draw(play_button);

		if (isHovered(settings_button)) m_window->draw(settings_button_hover);
		else m_window->draw(settings_button);

		if (isHovered(quit_button)) m_window->draw(quit_button_hover);
		else m_window->draw(quit_button);
	}
	else {
		if (isHovered(settings_button)) m_window->draw(settings_button_hover);
		else m_window->draw(settings_button);

		if (isHovered(quit_button)) m_window->draw(quit_button_hover);
		else m_window->draw(quit_button);
	}

	
}

//Находится ли спрайт под мышкой
bool Sigma::Menu::isHovered(const sf::Sprite & sprite) {
	return sprite.getGlobalBounds().contains(mouse.getPosition(*m_window).x, mouse.getPosition(*m_window).y);
}


//Апдейт
void Sigma::Menu::update() {
	
}

//Обработка клика мыши
void Sigma::Menu::on_mouse_click() {
	if (isHovered(play_button)) {
		*m_pause = false;
		state = State::PAUSE;
		play_button.setPosition(-300, 100);
		play_button_hover.setPosition(-300, 100);

	}

	if (isHovered(quit_button)) {
		m_window->close();
	}
}