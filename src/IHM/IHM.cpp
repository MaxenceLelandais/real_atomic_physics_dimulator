#include "IHM.h"

IHM::IHM()
{
}

void myFunction()
{
    std::cout << "La fonction myFunction a été appelée avec les paramètres : " << std::endl;
}

bool IHM::init(int SCREEN_WIDTH, int SCREEN_HEIGHT, sf::Uint8 *matrix, sf::Uint16 *id_matrix, std::map<int, std::map<std::string, std::function<void()>>> *map_event, bool *screenModified)
{

    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->matrix = matrix;
    this->map_event = map_event;

    rendu.init(SCREEN_WIDTH, SCREEN_HEIGHT, matrix, id_matrix, map_event, screenModified);
    menu();

    return true;
}

void IHM::menu()
{
    unsigned char black[4] = {0, 0, 0, 255};
    unsigned char grey[4] = {210, 210, 210, 255};
    unsigned char white[4] = {255, 255, 255, 255};
    unsigned char red[4] = {255, 0, 0, 255};

    int idNewSim, idLoadSim, idConfig, idLeave, idHelp, idInfos, idQuit;
    int size = 40;
    int widthButton = 350, heightButton = 100, border = 2, radius = 20, centerX = SCREEN_WIDTH / 2 - widthButton / 2, centerY = SCREEN_HEIGHT / 2 - heightButton / 2, footY = SCREEN_HEIGHT / 9;

    idQuit = rendu.ButtonRectCircleAngleBorderWithText(SCREEN_WIDTH-50, 50, 50, 50, radius, border, "X", size, black, black, red, red, black, black, myFunction);

    idNewSim = rendu.ButtonRectCircleAngleBorderWithText(centerX, footY, widthButton, heightButton, radius, border, "New simulation", size, black, black, grey, white, black, black, myFunction);

    idLoadSim = rendu.ButtonRectCircleAngleBorderWithText(centerX, 3 * footY, widthButton, heightButton, radius, border, "Load simulation", size, black, black, grey, white, black, black, myFunction);

    idConfig = rendu.ButtonRectCircleAngleBorderWithText(centerX, 6 * footY, widthButton, heightButton, radius, border, "Configuration", size, black, black, grey, white, black, black, myFunction);

    idNewSim = rendu.ButtonRectCircleAngleBorderWithText(centerX, 8 * footY, widthButton, heightButton, radius, border, "Leave", size, black, black, grey, white, black, black, myFunction);

    idNewSim = rendu.ButtonRectCircleAngleBorderWithText(SCREEN_WIDTH / 10, centerY, widthButton, heightButton, radius, border, "Help", size, black, black, grey, white, black, black, myFunction);

    idNewSim = rendu.ButtonRectCircleAngleBorderWithText(8 * SCREEN_WIDTH / 10, centerY, widthButton, heightButton, radius, border, "Informations", size, black, black, grey, white, black, black, myFunction);
}

void IHM::quit()
{
    release();
}

bool IHM::release()
{
    return true;
}
IHM::~IHM()
{
}