#pragma once

#include "Window/Window.h"
#include "IHM/IHM.h"

#include <functional>
#include <map>
#include <thread>

class Application
{
public:
	// Constructeur
	Application();

	bool init();
	bool release();

	// Destructeur
	~Application();

public:
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
	bool *screenModified = new bool;

	sf::Uint8 *matrix = new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4];
	sf::Uint16 *id_matrix = new sf::Uint16[SCREEN_WIDTH * SCREEN_HEIGHT];
	std::map<int, std::map<std::string, std::function<void()>>> *map_event = new std::map<int, std::map<std::string, std::function<void()>>>;

	Window window;
	IHM ihm;
};