#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <locale>
#include <codecvt>
#include "Logger.h"
#include <random>




#define LoadTexture(texture, path) {if (!texture.loadFromFile(path)) throw std::exception("Failed to load texture " + path);}




namespace Sigma {

	class Game;
	struct GameData;
	class Engine;
	class Menu;


}
