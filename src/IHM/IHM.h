#pragma once
#include <SFML/Graphics.hpp>
#include "GestionAffichage/Rendu.h"

#include <iostream>
#include <functional>
#include <map>
#include <chrono>

class IHM
{
public:
	IHM();

	bool init(int, int, sf::Uint8*, sf::Uint16*,std::map<int, std::map<std::string,std::function<void()>>>*, bool*);

	~IHM();

public:
	int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
	sf::Uint8* matrix;
	sf::Uint16* id_matrix;
	std::map<int, std::map<std::string,std::function<void()>>>* map_event;

	Rendu rendu;
	

public:
	void speedTest();
	
};