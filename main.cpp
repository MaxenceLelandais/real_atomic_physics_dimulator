#include "src/Application.h"
#include "src/Quality/Log.h"
#include <iostream>

int main()
{
    Log log;
    log.send("info", "Starting program.");
	Application app;
	// Initia(lisation de la fenêtre
    if (app.init()) {
        std::cout << "Erreur lors de l'initialisation de l'application." << std::endl;
        return false;
    }
    

	return 0;
}
