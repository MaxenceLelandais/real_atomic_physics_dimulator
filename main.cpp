#include "src/Application.h"
#include "src/Quality/Log.h"

int main()
{
    Log::getInstance()->logMessage("info", "Starting program.");

    Application app;
    Log::getInstance()->logMessage("info", "Application init.");
    if (app.init())
    {
        Log::getInstance()->logMessage("error", "Application init.");
        return false;
    }

    Log::getInstance()->logMessage("info", "Close program.");

    return 0;
}
