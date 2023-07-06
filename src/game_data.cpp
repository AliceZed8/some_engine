#include "game_data.h"

void Sigma::GameData::load_data() {
	INFO("Loading game data")
	if (!(std::filesystem::exists("data")))
		std::filesystem::create_directory("data");

	std::ifstream in("data/gamedata.sigma", std::ios::binary);

	data = new Data();
	if (data != nullptr) {
		INFO("Reading game data")
		if (in.is_open()) {
			in.read((char*)data, sizeof(data));
			std::cout << data->money << std::endl;
			std::cout << data->record1 << std::endl;
		}
		else {
			ERROR("Failed to read game data file data/gamedata.sigma");
			in.close();
		}
		
		return;
	}

	ERROR("Failed to allocate memory for game data");
}

void Sigma::GameData::save_data() {
	std::ofstream out("data/gamedata.sigma", std::ios::binary);

	if (out.is_open()) {
		INFO("Saving game data");
		out.write((char*)data, sizeof(data));
		return;
	}

	ERROR("Failed to save game data");
}