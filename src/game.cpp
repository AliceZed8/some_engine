#include "game.h"

//Чтение рецептов (Кодировка ANSI)
bool Sigma::Game::load_recipes() {
	std::ifstream in("assets/recipe_book.txt");

	if (in.is_open()) {
		RecipePage page;
		while (!in.eof()) {
			Recipe recipe;
			std::string info;
			//Строка с названием и ингредиентами
			std::getline(in, recipe.name);
			std::getline(in, info);

			//Читаем рецепт
			for (int i = 0; i < info.size(); i++) {
				switch (info[i])
				{
				case 'К':
					//Добавляем нужные спрайты
					recipe.elements.push_back(icon_sprites[0]);
					recipe.counter[0]++;
					break;

				case 'З':
					recipe.elements.push_back(icon_sprites[1]);
					recipe.counter[1]++;
					break;

				case 'С':
					recipe.elements.push_back(icon_sprites[2]);
					recipe.counter[2]++;
					break;

				case 'Ж':
					recipe.elements.push_back(icon_sprites[3]);
					recipe.counter[3]++;
					break;

				case 'Ч':
					recipe.elements.push_back(icon_sprites[4]);
					recipe.counter[4]++;
					break;
				}
			}

			//Пока страница с рецептами не заполнена добавляем рецепт
			if (page.recipes.size() < page.max_on_page) page.recipes.push_back(recipe);


			//Если страница заполнена, добавляем в книгу и очищаем страницу
			if (page.recipes.size() == page.max_on_page) {
				recipe_book.pages.push_back(page);
				page.recipes.clear();
			}


			//Добавляем рецепт
			recipe_book.recipes_list.push_back(recipe);
		}

		//Добавляем остатки от цикла
		if (!(page.recipes.empty())) recipe_book.pages.push_back(page);

		recipe_book.page_num = 0;
		//Настраиваем плюсики
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				recipe_book.plus[i][j].setTexture(plus_texture);
				//recipe_book.plus[i][j].setScale(0.7f, 0.7f);
			}
		}
		//Обновляем книгу
		update_recipe_book();
		return true;
	}
	else {
		ERROR("Failed to open recipe_book.txt");
		return false;
	}
}

//рендер книги
void Sigma::Game::draw_recipe_book() {

	for (int i = 0; i < recipe_book.pages[recipe_book.page_num].recipes.size(); i++) {
		//рисуем текст каждого рецепта
		m_window->draw(recipe_book.text[i]);

		for (int j = 0; j < recipe_book.pages[recipe_book.page_num].recipes[i].elements.size(); j++) {
			//рисуем элементы каждого рецепта
			m_window->draw(recipe_book.pages[recipe_book.page_num].recipes[i].elements[j]);
		}
	}
	//Рисуем плюсики между ингредиентами
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_window->draw(recipe_book.plus[i][j]);
		}
	}
}

//Обновление книги
void Sigma::Game::update_recipe_book() {
	for (int i = 0; i < recipe_book.pages[recipe_book.page_num].recipes.size(); i++) {
		//Настраиваем текущую страницу для рисования


		//Замена и настройка текста
		recipe_book.text[i].setFont(font);
		recipe_book.text[i].setFillColor(sf::Color::Black);
		recipe_book.text[i].setCharacterSize(14);
		recipe_book.text[i].setPosition(340, i * 50 + 110);

		//Фиксим строку и переводим в UTF8
		sf::String fixed(recipe_book.pages[recipe_book.page_num].recipes[i].name, std::locale("RU_ru"));
		recipe_book.text[i].setString(fixed);
		
		//Настраиваем положения и размер элементов
		for (int j = 0; j < recipe_book.pages[recipe_book.page_num].recipes[i].elements.size(); j++) {
			//Настройка элемента
			recipe_book.pages[recipe_book.page_num].recipes[i].elements[j].setPosition(340 + 50 * j, i * 50 + 130);
			recipe_book.pages[recipe_book.page_num].recipes[i].elements[j].setScale(0.4f, 0.4f);
			if (j == (recipe_book.pages[recipe_book.page_num].recipes[i].elements.size() - 1)) continue;

			//Настройка плюсиков
			recipe_book.plus[i][j].setPosition(372 + 50 * j, 137 + i * 50);

		}

	}
}

//пред страница
void Sigma::Game::prev_page() {
	if (recipe_book.page_num == 0) recipe_book.page_num = recipe_book.pages.size() - 1;
	else recipe_book.page_num--;

	update_recipe_book();
}

//след страница
void Sigma::Game::next_page() {
	if (recipe_book.page_num == (recipe_book.pages.size() - 1)) recipe_book.page_num = 0;
	else recipe_book.page_num++;

	update_recipe_book();
}

//Конструктор
Sigma::Game::Game(sf::RenderWindow* window, GameData* data, bool* pause) :
	m_window(window), m_data(data), m_pause(pause) {

	//Загрузка текстур
	if (!load_data()) m_window->close();

	//Загрузка рецептов
	if (!load_recipes()) m_window->close();

	//Тайм бар и его первоначальные настройки
	time_bar.setPosition(250, 150);
	time_bar_hover.setPosition(250, 150);
	
	time_bar_hover.setSize(sf::Vector2f(20.0f, 150.0f));
	time_bar_hover.setFillColor(sf::Color(255, 255, 255));
	time_bar_hover.setOutlineThickness(3.0f);
	time_bar_hover.setOutlineColor(sf::Color::Blue);

	time_bar.setFillColor(sf::Color::Red);

	//Счет и его первоначальные настройки
	balance_text.setFont(font);
	balance_text.setCharacterSize(16);
	balance_text.setPosition(70, 105);

	//Обновляем счет
	update_balance();
}

//Новый клиент
void Sigma::Game::new_client() {
	current = new Client();
	std::random_device rd;
	std::mt19937 gen(rd());



	current->client_type = gen() % 5;
	current->flask_type = gen() % 3;
	current->recipe_num = gen() % (recipe_book.recipes_list.size());
	current->clock.restart();

	time_bar.setPosition(250, 150);
	time_bar_hover.setPosition(250, 150);

	client_text.setFont(font);
	client_text.setColor(sf::Color::Black);
	client_text.setCharacterSize(16);
	client_text.setPosition(20, 23);

	std::string str;
	switch (current->flask_type)
	{
	case 0:
		str += "Взрывное зелье\n";
		break;
	case 1:
		str += "Походное зелье\n";
		break;
	case 2:
		str += "Длительное зелье\n";
		break;
	}

	str += "\"" + recipe_book.recipes_list[current->recipe_num].name + "\"";

	sf::String fixed(str, std::locale("RU_ru"));
	client_text.setString(fixed);
}

//Обновляем счет
void Sigma::Game::update_balance() {
	
	std::string str = "Счет: " + std::to_string(m_data->data->money);
	sf::String fixed(str, std::locale("RU_ru"));
	balance_text.setString(fixed);
}

//Находится ли спрайт под мышкой
bool Sigma::Game::isHovered(const sf::Sprite& sprite) {
	return sprite.getGlobalBounds().contains(mouse.getPosition(*m_window).x, mouse.getPosition(*m_window).y);
}

//Обработка клика мыши
void Sigma::Game::on_mouse_click() {
	if (!*m_pause) {
		for (int i = 0; i < 5; i++) {
			//Если нажат ингредиент
			if (isHovered(element_sprites[i])) {
				
				//Если в тигеле менее 5 ингрелиентов
				if (elements_in_tigel.size() < 5) {
					splash_s.play();
					tigel_counter[i]++;
					icon_sprites[i].setScale(0.5f, 0.5f);
					//Расставляем их в порядке
					switch (elements_in_tigel.size())
					{
					case 0:
						icon_sprites[i].setPosition(40, 750);
						break;
					case 1:
						icon_sprites[i].setPosition(80, 750);
						break;
					case 2:
						icon_sprites[i].setPosition(120, 750);
						break;
					case 3:
						icon_sprites[i].setPosition(160, 750);
						break;
					case 4:
						icon_sprites[i].setPosition(200, 750);
						break;
					}
					elements_in_tigel.push_back(icon_sprites[i]);
				}

				//Если нет то очищаем
				else {
					elements_in_tigel.clear();
					std::memset(tigel_counter, 0, sizeof(tigel_counter));
				}

				break;
			
			}
		}

		if (prev.contains(mouse.getPosition(*m_window).x, mouse.getPosition(*m_window).y)) prev_page();
		
		if (next.contains(mouse.getPosition(*m_window).x, mouse.getPosition(*m_window).y)) next_page();

		if (elements_in_tigel.size() == 5) {
			for (int i = 0; i < 3; i++) {
				if (isHovered(flask_sprites[i])) {
					elements_in_tigel.clear();
					finish_the_order(i);
					std::memset(tigel_counter, 0, sizeof(tigel_counter));
					break;
				}
			}
		}

		if (isHovered(money_sprite)) {
			if (money) {
				take_the_money_s.play();
				money = false;
				m_data->data->money += money_count;
				money_count = 0;
				update_balance();
			}
			
		}
		
	}
}

//Закончить заказ
void Sigma::Game::finish_the_order(int i) {
	current->waiting = false;
	current->finished = true;
	filling_the_flask_s.play();

	if (i == current->flask_type) {
		bool test = true;
		for (int k = 0; k < 5; k++) {
			if (!(recipe_book.recipes_list[current->recipe_num].counter[k] == tigel_counter[k]))
				test = false;
		}

		if (test) {
			money_for_order_s.play();
			money = true;
			money_count += 500;
		}
	}

}

//Обработка нажатий кл.
void Sigma::Game::on_keyboard(const sf::Event& event) {
	
	// Если нажата С и тигель активен, то очищаем тигель.
	if ((event.key.code == sf::Keyboard::C) && (isHovered(tigel_sprite))) {
		elements_in_tigel.clear();
		std::memset(tigel_counter, 0, sizeof(tigel_counter));
	}

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
		m_window->draw(client_text);
	}
	
	// Элементы
	for (int i = 0; i < 5; i++) 
		m_window->draw(element_sprites[i]);

	// мини элементы в тигеле
	for (int i = 0; i < elements_in_tigel.size(); i++) 
		m_window->draw(elements_in_tigel[i]);

	//тигель
	m_window->draw(tigel_sprite);

	//книга рецептов
	draw_recipe_book();

	//колбы
	for (int i = 0; i < 3; i++) m_window->draw(flask_sprites[i]);

	//счет
	m_window->draw(balance_text);

	// Если есть наведенный элемент то рисуем другой его вариант
	if (hover) m_window->draw(HoveredSprite);

	//деньги
	if (money) m_window->draw(money_sprite);

}

//Апдейт
void Sigma::Game::update() {
	//Если игра не приостановлена и нет текущего клиента, то создаем нового
	if (!(*m_pause) && (current == nullptr)) new_client();

	//Если есть клиент и игра не приостановлена
	if ((current != nullptr) && (!(*m_pause))) {

		//Если клиент идет к окошку
		if (!current->waiting) {
			if (walk_clock.getElapsedTime().asMilliseconds() > 700) {
				walking_s.play();
				walk_clock.restart();
			}


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
				new_client();

				//обнуляем время проведенное при паузе
				pause_elapsed = 0;
			}
		}

		//Если клиент ждет...
		if (current->waiting) {
			//Если его время ожидания истекло, обновляем параметры. Клиент уходит
			if (current->clock.getElapsedTime().asMilliseconds() - pause_elapsed > wait_time)
			{
				current->finished = true;
				current->waiting = false;
			}

			//Если клиент еще ждет свой заказ
			if (!current->finished) {
				//Обновляем полоску таймбара
				time_bar.setPosition(
					250, 150 + 150.0f * (current->clock.getElapsedTime().asMilliseconds() - pause_elapsed) / wait_time
				);

				time_bar.setSize(
					sf::Vector2f(
						20.0f,
						150.0f - 150.0f * (current->clock.getElapsedTime().asMilliseconds() - pause_elapsed) / wait_time
					)
				);
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
bool Sigma::Game::load_data() {
	try {
		//Лаборатория
		if (!main_texture.loadFromFile("assets/main.png")) 
			throw std::exception("Failed to load assets/main.png");

		main_sprite.setTexture(main_texture);
		//Настройка под наше разрешение
		main_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);

		//Фон
		if (!backg_texture.loadFromFile("assets/background.png")) 
			throw std::exception("Failed to load assets/background.png");

		backg_sprite.setTexture(backg_texture);

		//Настройка под наше разрешение
		backg_sprite.setScale((float)m_window->getSize().x / 960, (float)m_window->getSize().y / 1080);

		//Тигель
		if (!tigel_texture.loadFromFile("assets/tigel.png")) 
			throw std::exception("Failed to load assets/tigel.png");

		tigel_sprite.setTexture(tigel_texture);
		tigel_sprite.setScale(0.6f, 0.6f);
		tigel_sprite.setPosition(10.0f, 470.0f);

		for (int i = 0; i < 5; i++) {
			//Элементы
			if (!element_textures[i].loadFromFile("assets/elements/" + std::to_string(i + 1) + ".png")) 
				throw std::exception("Failed to load elements /assets/elements/");

			element_sprites[i].setTexture(element_textures[i]);
			element_sprites[i].setScale(0.5f, 0.5f);

			//Иконки
			if (!icon_textures[i].loadFromFile("assets/icons/" + std::to_string(i + 1) + ".png")) 
				throw std::exception("Failed to load elements /assets/icons/");
			icon_sprites[i].setTexture(icon_textures[i]);

			//Элементы при наведении
			if (!element_hover_textures[i].loadFromFile("assets/elements/" + std::to_string(i + 1) + "h.png")) 
				throw std::exception("Failed to load element hovers /assets/elements/");
			element_hover_sprites[i].setTexture(element_hover_textures[i]);
			element_hover_sprites[i].setScale(0.5f, 0.5f);

			//Клиенты
			if (!client_textures[i].loadFromFile("assets/clients/" + std::to_string(i + 1) + ".png")) 
				throw std::exception("Failed to load clients assets/clients/");

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
		if (!font.loadFromFile("assets/fonts/font.ttf")) 
			throw std::exception("Failed to load font assets/fonts/font.ttf");

		//Плюсик
		if (!plus_texture.loadFromFile("assets/icons/plus.png"))  
			throw std::exception("Failed to load + texture assets/icons/plus.png");


		//Колбы
		for (int i = 0; i < 3; i++) {
			if (!flask_textures[i].loadFromFile("assets/flask/" + std::to_string(i + 1) + ".png")) 
				throw std::exception("Failed to load flask  /assets/flask/");
			flask_sprites[i].setTexture(flask_textures[i]);
			flask_sprites[i].setScale(0.6f, 0.6f);
		}

		flask_sprites[0].setPosition(300, 400);
		flask_sprites[1].setPosition(400, 400);
		flask_sprites[2].setPosition(500, 400);


		//Деньги

		if (!money_texture.loadFromFile("assets/money.png"))
			throw std::exception("Failed to load assets/money.png");


		money_sprite.setTexture(money_texture);
		money_sprite.setScale(0.5f, 0.5f);
		money_sprite.setPosition(30, 320);





		//Звуки
		if (!walking_sb.loadFromFile("assets/sound/walking.wav"))
			throw std::exception("Failed to load assets/sound/walking.wav");

		if (!splash_sb.loadFromFile("assets/sound/splash.wav"))
			throw std::exception("Failed to load assets/sound/splash.wav");

		if (!filling_the_flask_sb.loadFromFile("assets/sound/filling_the_flask.wav"))
			throw std::exception("Failed to load assets/sound/filling_the_flask.wav");

		if (!money_for_order_sb.loadFromFile("assets/sound/money_for_the_order.ogg"))
			throw std::exception("Failed to load assets/sound/money_for_the_order.ogg");

		if (!take_the_money_sb.loadFromFile("assets/sound/take_the_money.ogg"))
			throw std::exception("Failed to load assets/sound/take_the_money.ogg");


		filling_the_flask_s.setBuffer(filling_the_flask_sb);
		filling_the_flask_s.setVolume(20);

		money_for_order_s.setBuffer(money_for_order_sb);
		take_the_money_s.setBuffer(take_the_money_sb);

		splash_s.setBuffer(splash_sb);
		splash_s.setVolume(10);


		walking_s.setBuffer(walking_sb);
	}
	catch (std::exception & e) {
		ERROR(e.what());
		return false;
	}
	return true;
}
