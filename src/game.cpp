#include "game.h"

Sigma::Game::Game(sf::RenderWindow* window, GameData* data, bool* pause) :
	m_window(window), m_data(data), m_pause(pause) {
	
	//�������� �������
	load_data();

	//���� ��� � ��� �������������� ���������
	time_bar.setPosition(100, 100);
	time_bar_hover.setPosition(100, 100);
	
	time_bar_hover.setSize(sf::Vector2f(60.0f, 10.0f));
	time_bar_hover.setFillColor(sf::Color(255, 255, 255));
	time_bar_hover.setOutlineThickness(2.0f);
	time_bar_hover.setOutlineColor(sf::Color(0, 255, 255));

	time_bar.setFillColor(sf::Color(255, 0, 0));
}

//��������� �� ������ ��� ������
bool Sigma::Game::isHovered(const sf::Sprite& sprite) {
	return sprite.getGlobalBounds().contains(mouse.getPosition(*m_window).x, mouse.getPosition(*m_window).y);
}

//��������� ����� ����
void Sigma::Game::on_mouse_click() {
	for (int i = 0; i < 5; i++) {
		if (isHovered(element_sprites[i])) {
			//���� ����� ����������

			//���� � ������ ����� 5 ������������
			if (elements_in_tigel.size() < 5) {

				//����������� �� � �������
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

			//���� ��� �� �������
			else elements_in_tigel.clear();

			break;
			
		}
	}
}

//��������� ������� ��.
void Sigma::Game::on_keyboard(const sf::Event& event) {
	
	// ���� ������ � � ������ �������, �� ������� ������.
	if ((event.key.code == sf::Keyboard::C) && (isHovered(tigel_sprite))) elements_in_tigel.clear();

	// ���� ������ ������ �����
	if (event.key.code == sf::Keyboard::Escape) {
		//���� ���� ���� ��������������
		if (*m_pause) {
			// ������������
			*m_pause = false;
			if (current->waiting)
				//���� ������ ���� �� ����������� ����� ����������� � �����
				pause_elapsed += pause_clock.getElapsedTime().asMilliseconds();
		}
		else {
			*m_pause = true;
			// ���� ������ ����, �������� ������
			if (current->waiting) pause_clock.restart();
		}
	}
}

//���������
void Sigma::Game::render() {
	//���
	m_window->draw(backg_sprite);

	//������
	if (current != nullptr) {
		m_window->draw(client_sprites[current->client_type]);
	}

	//�����������
	m_window->draw(main_sprite);

	//�������
	if ((current != nullptr) && (current->waiting)) {
		m_window->draw(time_bar_hover);
		m_window->draw(time_bar);
	}
	
	// ��������, ���� ��������
	for (int i = 0; i < 5; i++) {
		m_window->draw(element_sprites[i]);
	}
	for (int i = 0; i < elements_in_tigel.size(); i++) {
		m_window->draw(elements_in_tigel[i]);
	}

	m_window->draw(tigel_sprite);

	// ���� ���� ���������� ������� �� ������ ������ ��� �������
	if (hover) m_window->draw(HoveredSprite);

}

//������
void Sigma::Game::update() {
	//���� ���� �� �������������� � ��� �������� �������, �� ������� ������
	if (!(*m_pause) && (current == nullptr)) current = new Client();

	//���� ���� ������ � ���� �� ��������������
	if ((current != nullptr) && (!(*m_pause))) {

		//���� ������ ���� � ������
		if (!current->waiting) {
			//������� �������
			client_sprites[current->client_type].move(client_speed, 0.0f);

			//���� ����� �� ������, ��������� ��������� � �������.
			if ((client_sprites[current->client_type].getPosition().x >= 50) && (!current->finished)) {
				current->waiting = true;
				current->clock.restart();
			}

			//���� ����, �� ���������� ������ � ������ ���������. ������� ������ �������
			if (client_sprites[current->client_type].getPosition().x >= 300) {
				client_sprites[current->client_type].setPosition(-120, 180);
				delete current;
				current = new Client();

				//�������� ����� ����������� ��� �����
				pause_elapsed = 0;
			}
		}

		//���� ������ ����...
		if (current->waiting) {
			//���� ��� ����� �������� �������, ��������� ���������. ������ ������
			if (current->clock.getElapsedTime().asMilliseconds() - pause_elapsed > 15000)
			{
				current->finished = true;
				current->waiting = false;
			}

			//���� ������ ��� ���� ���� �����
			if (!current->finished) {
				//��������� ������� ��������
				time_bar.setSize(
					sf::Vector2f(
						60.0f - 60.0f * (current->clock.getElapsedTime().asMilliseconds() - pause_elapsed) / 15000,
						10.0f
					));
			}
		}
	}
	//���������� ������
	hover = false;
	for (int i = 0; i < 5; i++) {
		if (isHovered(element_sprites[i])) {
			HoveredSprite = element_hover_sprites[i];
			hover = true;
			break;
		}
	}
}

//�������� ������� � ��������.
void Sigma::Game::load_data() {
	//�����������
	main_texture.loadFromFile("assets/main.png");
	main_sprite.setTexture(main_texture);
	//��������� ��� ���� ����������
	main_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);

	//���
	backg_texture.loadFromFile("assets/background.png");
	backg_sprite.setTexture(backg_texture);
	//��������� ��� ���� ����������
	backg_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);


	//������
	tigel_texture.loadFromFile("assets/tigel.png");
	tigel_sprite.setTexture(tigel_texture);
	tigel_sprite.setScale(0.6f, 0.6f);
	tigel_sprite.setPosition(10.0f, 470.0f);

	for (int i = 0; i < 5; i++) {
		//��������
		element_textures[i].loadFromFile("assets/elements/" + std::to_string(i + 1) + ".png");
		element_sprites[i].setTexture(element_textures[i]);
		element_sprites[i].setScale(0.5f, 0.5f);

		//���� ��������
		mini_element_sprites[i].setTexture(element_textures[i]);
		mini_element_sprites[i].setScale(0.15f, 0.15f);

		//�������� ��� ���������
		element_hover_textures[i].loadFromFile("assets/elements/" + std::to_string(i + 1) + "h.png");
		element_hover_sprites[i].setTexture(element_hover_textures[i]);
		element_hover_sprites[i].setScale(0.5f, 0.5f);

		//�������
		client_textures[i].loadFromFile("assets/clients/" + std::to_string(i + 1) + ".png");
		client_sprites[i].setTexture(client_textures[i]);
		client_sprites[i].setScale(0.5f, 0.5f);
		client_sprites[i].setPosition(-120, 180);
	}
	//�������� � �� ����������
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

	


	//������
	font.loadFromFile("assets/fonts/font.ttf");

}