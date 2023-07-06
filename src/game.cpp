#include "game.h"

Sigma::Game::Game(sf::RenderWindow* window, GameData* data, bool* pause) :
	m_window(window), m_data(data), m_pause(pause) {
	
	//Загрузка текстур
	load_data();

	//Тайм бар и его первоначальные настройки
	time_bar.setPosition(100, 100);
	time_bar_hover.setPosition(100, 100);
	
	time_bar_hover.setSize(sf::Vector2f(60.0f, 10.0f));
	time_bar_hover.setFillColor(sf::Color(255, 255, 255));
	time_bar_hover.setOutlineThickness(2.0f);
	time_bar_hover.setOutlineColor(sf::Color(0, 255, 255));

	time_bar.setFillColor(sf::Color(255, 0, 0));
}

//Находится ли спрайт под мышкой
bool Sigma::Game::isHovered(const sf::Sprite& sprite) {
	return sprite.getGlobalBounds().contains(mouse.getPosition(*m_window).x, mouse.getPosition(*m_window).y);
}

//Обработка клика мыши
void Sigma::Game::on_mouse_click() {
	for (int i = 0; i < 5; i++) {
		if (isHovered(element_sprites[i])) {
			//Если нажат ингредиент

			//Если в тигеле менее 5 ингрелиентов
			if (elements_in_tigel.size() < 5) {

				//Расставляем их в порядке
				switch (elements_in_tigel.size())
				{
				case 0:
					mini_element_sprites[i].setPosition(20, 750);
					break;
				case 1:
					mini_element_sprites[i].setPosition(55, 750);
					break;
				case 2:
					mini_element_sprites[i].setPosition(85, 750);
					break;
				case 3:
					mini_element_sprites[i].setPosition(115, 750);
					break;
				case 4:
					mini_element_sprites[i].setPosition(155, 750);
					break;
				}
				elements_in_tigel.push_back(mini_element_sprites[i]);
			}

			//Если нет то очищаем
			else elements_in_tigel.clear();

			break;
			
		}
	}
}

//Обработка нажатий кл.
void Sigma::Game::on_keyboard(const sf::Event& event) {
	
	// Если нажата С и тигель активен, то очищаем тигель.
	if ((event.key.code == sf::Keyboard::C) && (isHovered(tigel_sprite))) elements_in_tigel.clear();

	// Если нажата кнопка паузы
	if (event.key.code == sf::Keyboard::Escape) {
		//Если игра была приостановлена
		if (*m_pause) {
			// Возобновляем
			*m_pause = false;
			if (current->waiting)
				//Если клиент ждет то увеличиваем время проведенное в паузе
				pause_elapsed += pause_clock.getElapsedTime().asMilliseconds();
		}
		else {
			*m_pause = true;
			// Если клиент ждет, включаем таймер
			if (current->waiting) pause_clock.restart();
		}
	}
}

//рендеринг
void Sigma::Game::render() {
	//Фон
	m_window->draw(backg_sprite);

	//Клиент
	if (current != nullptr) {
		m_window->draw(client_sprites[current->client_type]);
	}

	//Лаборатория
	m_window->draw(main_sprite);

	//Таймбар
	if ((current != nullptr) && (current->waiting)) {
		m_window->draw(time_bar_hover);
		m_window->draw(time_bar);
	}
	
	// Элементы, мини элементы
	for (int i = 0; i < 5; i++) {
		m_window->draw(element_sprites[i]);
	}
	for (int i = 0; i < elements_in_tigel.size(); i++) {
		m_window->draw(elements_in_tigel[i]);
	}

	m_window->draw(tigel_sprite);

	// Если есть наведенный элемент то рисуем другой его вариант
	if (hover) m_window->draw(HoveredSprite);

}

//Апдейт
void Sigma::Game::update() {
	//Если игра не приостановлена и нет текущего клиента, то создаем нового
	if (!(*m_pause) && (current == nullptr)) current = new Client();

	//Если есть клиент и игра не приостановлена
	if ((current != nullptr) && (!(*m_pause))) {

		//Если клиент идет к окошку
		if (!current->waiting) {
			//Двигаем клиента
			client_sprites[current->client_type].move(client_speed, 0.0f);

			//Если дошел до окошка, обновляем параметры и счетчик.
			if ((client_sprites[current->client_type].getPosition().x >= 50) && (!current->finished)) {
				current->waiting = true;
				current->clock.restart();
			}

			//Если ушел, то отправляем спрайт в дефолт положение. Создаем нового клиента
			if (client_sprites[current->client_type].getPosition().x >= 300) {
				client_sprites[current->client_type].setPosition(-120, 180);
				delete current;
				current = new Client();

				//обнуляем время проведенное при паузе
				pause_elapsed = 0;
			}
		}

		//Если клиент ждет...
		if (current->waiting) {
			//Если его время ожидания истекло, обновляем параметры. Клиент уходит
			if (current->clock.getElapsedTime().asMilliseconds() - pause_elapsed > 15000)
			{
				current->finished = true;
				current->waiting = false;
			}

			//Если клиент еще ждет свой заказ
			if (!current->finished) {
				//Обновляем полоску таймбара
				time_bar.setSize(
					sf::Vector2f(
						60.0f - 60.0f * (current->clock.getElapsedTime().asMilliseconds() - pause_elapsed) / 15000,
						10.0f
					));
			}
		}
	}
	//Наведенный спрайт
	hover = false;
	for (int i = 0; i < 5; i++) {
		if (isHovered(element_sprites[i])) {
			HoveredSprite = element_hover_sprites[i];
			hover = true;
			break;
		}
	}
}

//Загрузка текстур и спрайтов.
void Sigma::Game::load_data() {
	//Лаборатория
	main_texture.loadFromFile("assets/main.png");
	main_sprite.setTexture(main_texture);
	//Настройка под наше разрешение
	main_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);

	//Фон
	backg_texture.loadFromFile("assets/background.png");
	backg_sprite.setTexture(backg_texture);
	//Настройка под наше разрешение
	backg_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);


	//Тигель
	tigel_texture.loadFromFile("assets/tigel.png");
	tigel_sprite.setTexture(tigel_texture);
	tigel_sprite.setScale(0.6f, 0.6f);
	tigel_sprite.setPosition(10.0f, 470.0f);

	for (int i = 0; i < 5; i++) {
		//Элементы
		element_textures[i].loadFromFile("assets/elements/" + std::to_string(i + 1) + ".png");
		element_sprites[i].setTexture(element_textures[i]);
		element_sprites[i].setScale(0.5f, 0.5f);

		//Мини элементы
		mini_element_sprites[i].setTexture(element_textures[i]);
		mini_element_sprites[i].setScale(0.15f, 0.15f);

		//Элементы при наведении
		element_hover_textures[i].loadFromFile("assets/elements/" + std::to_string(i + 1) + "h.png");
		element_hover_sprites[i].setTexture(element_hover_textures[i]);
		element_hover_sprites[i].setScale(0.5f, 0.5f);

		//Клиенты
		client_textures[i].loadFromFile("assets/clients/" + std::to_string(i + 1) + ".png");
		client_sprites[i].setTexture(client_textures[i]);
		client_sprites[i].setScale(0.5f, 0.5f);
		client_sprites[i].setPosition(-120, 180);
	}
	//Элементы и их координаты
	element_sprites[0].setPosition(280, 510);
	element_sprites[1].setPosition(390, 510);
	element_sprites[2].setPosition(470, 510);
	element_sprites[3].setPosition(300, 650);
	element_sprites[4].setPosition(440, 650);

	element_hover_sprites[0].setPosition(280, 510);
	element_hover_sprites[1].setPosition(390, 510);
	element_hover_sprites[2].setPosition(470, 510);
	element_hover_sprites[3].setPosition(300, 650);
	element_hover_sprites[4].setPosition(440, 650);

	


	//Шрифты
	font.loadFromFile("assets/fonts/font.ttf");

}