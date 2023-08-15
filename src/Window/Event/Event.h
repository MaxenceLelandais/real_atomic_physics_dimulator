#pragma once
#include <string>
#include <SFML/Window/Event.hpp>

class Event
{
public:
	Event();
	~Event();

	std::string decodeEvent(sf::Event);

	int mouse_x;
	int mouse_y;
};