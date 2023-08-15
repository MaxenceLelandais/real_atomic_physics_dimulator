#include "IHM.h"

IHM::IHM()
{
    
}

void myFunction()
{
    std::cout << "La fonction myFunction a été appelée avec les paramètres : "<<std::endl;
}

bool IHM::init(int SCREEN_WIDTH, int SCREEN_HEIGHT,sf::Uint8* matrix,sf::Uint16* id_matrix,std::map<int, std::map<std::string,std::function<void()>>>* map_event)
{
    
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->matrix = matrix;
    this->map_event = map_event;
    
    rendu.init(SCREEN_WIDTH, SCREEN_HEIGHT, matrix, id_matrix, map_event);
    

    unsigned char color[4] = {0,0,0,255};
    unsigned char color2[4] = {255,255,255,255};

    // rendu.Button(0, 0, 200, 200, color, color2, myFunction);
    rendu.text(0, 0, "New simulation", 30, color, color2);

    return true;
}



void IHM::speedTest()
{
    unsigned char color[4] = {255,128,0,255};
    // rendu.rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, color);
    float sum = 0.0;
    float nombre = 0.0;

    while (true){
        nombre ++;

        // Mesurer le temps d'exécution
        auto startTime = std::chrono::high_resolution_clock::now();

        rendu.rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        sum+=duration.count();
        std::cout << "Temps d'exécution de la ligne rendu.rect : " << 1/((sum/nombre)/1000) << " fps." << std::endl;


    }
}

IHM::~IHM()
{
	
}