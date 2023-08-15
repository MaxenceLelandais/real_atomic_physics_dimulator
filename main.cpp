#include "src/Application.h"
#include <iostream>
int main()
{

	Application app;
	// Initialisation de la fenêtre
    if (app.init()) {
        std::cout << "Erreur lors de l'initialisation de l'application." << std::endl;
        return false;
    }

	return 0;
}
