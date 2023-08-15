#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <unistd.h>
#include <chrono>

class Window
{
public:

    // Constructeur
    Window();

    bool init(int, int, sf::Uint8*, sf::Uint16*,std::map<int, std::map<std::string,std::function<void()>>> *);
    bool release();

    // Destructeur
    ~Window();

    void refresh();

    void handleEvents();
    void draw();
    void update();
    std::string encodeEvent(sf::Event);

    int SCREEN_WIDTH = 1920;
    int SCREEN_HEIGHT = 1080;
    int actual_id = 0;
    int mouse_x = 0;
    int mouse_y = 0;
    std::string code_event;

	std::map<int, std::map<std::string,std::function<void()>>>* map_event;

    sf::RenderWindow fenetre;
    sf::Texture texture;
    sf::Uint8* matrix;
    sf::Uint16* id_matrix;
    sf::Sprite sprite;
    sf::Event event;
};