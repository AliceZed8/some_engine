#pragma once
#include "pch.h"

class Sigma::Engine {
	private:
		std::string m_title;
		uint16_t m_width, m_height;
		sf::RenderWindow* window;
		sf::Clock clock;
		Game* game;
		Menu* menu;
		GameData* data;
		bool* pause;
		float want_fps = 60;

	public:
		Engine(const std::string& title = "Title", uint16_t w = 400, uint16_t h = 600);
		void run();
		void update();
		~Engine();

};




