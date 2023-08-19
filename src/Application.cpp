#include "Application.h"
#include "Quality/Log.h"

Application::Application()
{
	
}
bool Application::init()
{
    // ihm.init(SCREEN_WIDTH, SCREEN_HEIGHT, matrix, id_matrix, map_event);
    if (!window.init(SCREEN_WIDTH, SCREEN_HEIGHT, matrix, id_matrix, map_event, screenModified)) {
        std::cout << "Erreur lors de l'initialisation de la fenêtre." << std::endl;
        return false;
    }
    Log log;
    log.send("info", "Init window.");

    std::thread refreshThread([&]() {
        ihm.init(SCREEN_WIDTH, SCREEN_HEIGHT, matrix, id_matrix, map_event, screenModified);
    });
    refreshThread.join();
    
    log.send("info", "Init IHM.");


    window.refresh();


    // Libération des ressources
    window.release();

	return true;
}
        
 
bool Application::release()
{
	window.release();
	delete matrix;
    delete id_matrix;
    delete map_event;
	
	return true;
}

Application::~Application()
{

}