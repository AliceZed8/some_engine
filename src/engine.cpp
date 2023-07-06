#include "engine.h"
#include "game.h"
#include "game_data.h"
#include "menu.h"


std::ofstream Logger::Log::out;

Sigma::Engine::Engine(const std::string& title, uint16_t w, uint16_t h):
	m_title(title), m_width(w), m_height(h)
{
	//�������� ����, ������ ������� ������, ������ ����
	window = new sf::RenderWindow(sf::VideoMode(w, h), m_title, sf::Style::Titlebar | sf::Style::Close);
	pause = new bool(true);
	data = new GameData();
	game = new Game(window, data, pause);
	menu = new Menu(window, data, pause);
	
	//�������� ����� ����������� ������
	data->load_data();
	window->setActive();

	//���� ��� ������
	if (data->data == nullptr) {
		window->close();
	}
	
	
}

void Sigma::Engine::run() {
	INFO("Engine is running");
	if (window == nullptr) {
		ERROR("RenderWindow is nullptr");
		return;
	}
	clock.restart();

	while (window->isOpen()) {
		window->clear(sf::Color::Black);

		update();
		game->render();

		if (*pause) menu->draw();

		window->display();
		//�������� ���
		int frame_duration = clock.getElapsedTime().asMilliseconds();
		int time_to_sleep = int(1000.f / want_fps) - frame_duration;
		if (time_to_sleep > 0) sf::sleep(sf::milliseconds(time_to_sleep));
		clock.restart();
	}


	//��������� ������
	data->save_data();
}


// ������
void Sigma::Engine::update() {
	sf::Event event;
	menu->update();
	game->update();

	//������������ �������
	while (window->pollEvent(event))
	{
		//X
		if (event.type == sf::Event::Closed) window->close();

		//Click
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			game->on_mouse_click();
			if (*pause) menu->on_mouse_click();
		}

		//Keyboard
		if (event.type == sf::Event::KeyReleased) {
			game->on_keyboard(event);
		}
	}
}

Sigma::Engine::~Engine() {
	if (window != nullptr) delete window;
	if (game != nullptr) delete game;
	if (menu != nullptr) delete menu;
	if (pause != nullptr) delete pause;
	if (data != nullptr) delete data;
}




