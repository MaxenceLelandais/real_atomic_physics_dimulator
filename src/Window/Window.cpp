#include "Window.h"

Window::Window() : fenetre(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Affichage des pixels", sf::Style::Fullscreen)//Default, Fullscreen
{
}

bool Window::init(int SCREEN_WIDTH, int SCREEN_HEIGHT, sf::Uint8 *matrix, sf::Uint16 *id_matrix, std::map<int, std::map<std::string, std::function<void()>>> *map_event, bool *screenModified)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->matrix = matrix;
    this->id_matrix = id_matrix;
    this->map_event = map_event;
    this->screenModified = screenModified;

    std::fill_n(matrix, SCREEN_WIDTH * SCREEN_HEIGHT * 4, 255);
    std::fill_n(id_matrix, SCREEN_WIDTH * SCREEN_HEIGHT, 0);

    texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    texture.update(matrix);

    sprite.setTexture(texture);

    return true;
}

void Window::draw()
{
    // Effacement de la fenêtre
    fenetre.clear();

    // Affichage du sprite
    fenetre.draw(sprite);
}

void Window::handleEvents()
{

    while (fenetre.pollEvent(event))
    {

        sf::Vector2i mousePos = sf::Mouse::getPosition(fenetre);
        mouse_x = mousePos.x;
        mouse_y = mousePos.y;

        code_event = encodeEvent(event);

        if (code_event == "quit")
        {
            release();
            fenetre.close();
        }
        if (code_event != "None")
        {
            actual_id = (int)id_matrix[mouse_y * SCREEN_WIDTH + mouse_x];

            if ((*map_event).count(actual_id))
                if ((*map_event)[actual_id].count(code_event))
                    (*map_event)[actual_id][code_event]();
        }
    }
}

std::string Window::encodeEvent(sf::Event event)
{
    std::string code = "None";

    if (event.type == sf::Event::Closed)
    {
        code = "quit";
    }

    // Récupérer les coordonnées du curseur de la souris
    if (event.type == sf::Event::MouseMoved)
    {
        code = "MouseMoved";
    }

    // Gérer les événements de souris
    if (event.type == sf::Event::MouseButtonPressed)
    {

        if (event.mouseButton.button == sf::Mouse::Left)
            code = "ButtonLeftPressed";
        else if (event.mouseButton.button == sf::Mouse::Right)
            code = "ButtonRightPressed";
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
            code = "ButtonLeftReleased";
        else if (event.mouseButton.button == sf::Mouse::Right)
            code = "ButtonRightReleased";
    }

    // Gérer les événements de clavier
    else if (event.type == sf::Event::KeyPressed)
    {
        std::cout << event.key.code << std::endl;
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        std::cout << event.key.code << std::endl;
    }

    return code;
}

void Window::update()
{
    // Rafraîchissement de la fenêtre

    texture.update(matrix);
    fenetre.display();
}

void Window::refresh()
{
    int fps = 60;
    int microSecPerFrame = 1000000 / fps;
    // Boucle principale du programme
    bool start = true;

    while (fenetre.isOpen())
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        handleEvents();
        if (true)//*screenModified)
        {
            draw();
            update();
            if (start)
            {
                start = false;
            }
            else
            {
                *screenModified = false;
            }
        }

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime);

        if (duration.count() < microSecPerFrame)
        {
            usleep(microSecPerFrame - duration.count());
        }
    }
}

bool Window::release()
{
    return true;
}

Window::~Window()
{
}