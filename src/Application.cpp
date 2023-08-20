#include "Application.h"
#include "Quality/Log.h"

Application::Application()
{
}
bool Application::init()
{
    Log::getInstance()->logMessage("info","Init window.");
    
    if (!window.init(SCREEN_WIDTH, SCREEN_HEIGHT, matrix, id_matrix, map_event, screenModified))
    {
        Log::getInstance()->logMessage("error","Init window.");
        return false;
    }

    Log::getInstance()->logMessage("info","Start thread ihm.");
    std::thread refreshThread([&]()
    { 
        Log::getInstance()->logMessage("info","Init IHM.");
        if(!ihm.init(SCREEN_WIDTH, SCREEN_HEIGHT, matrix, id_matrix, map_event, screenModified))
        {
            Log::getInstance()->logMessage("error","Init IHM.");
        }; 
    });
    Log::getInstance()->logMessage("info","Join thread IHM.");
    refreshThread.join();

    Log::getInstance()->logMessage("info","Refresh window.");

    window.refresh();

    Log::getInstance()->logMessage("info","Release window.");
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