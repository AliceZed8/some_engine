#pragma once
#include "pch.h"
#include <filesystem>

struct Sigma::GameData {
	struct Data {
	uint64_t money = 100;
	uint64_t record1 = 0;
	uint64_t record2 = 0;
	uint64_t record3 = 0;
	uint8_t sound = 128;
	};
	Data* data = nullptr;
	GameData();
	void load_data();
	void save_data();
	~GameData();
};