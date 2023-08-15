#include "Event.h"
#include <string>


Event::Event()
{
    
}

std::string Event::decodeEvent(sf::Event event)
{

    if (event.type == sf::Event::Closed)
    {
        return "close";
    }
            
    // Récupérer les coordonnées du curseur de la souris
    if (event.type == sf::Event::MouseMoved)
    {
        
        
    }
        
    // Gérer les événements de souris
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
            
        else if (event.mouseButton.button == sf::Mouse::Right)
            
    }

    // Gérer les événements de clavier
    if (event.type == sf::Event::KeyPressed)
    {
        return "key-"+event.key.code;
    }
}

Event::~Event()
{
	
}