#include "Rendu.h"

Rendu::Rendu()
{

}

void Rendu::Button(int x, int y, int width, int height, unsigned char RGBA_Down[4], unsigned char RGBA_Up[4], std::function<void()> func)
{
    int id = rect(x, y, width, height, RGBA_Up);
    bind(id, "ButtonLeftPressed", [this,x, y, width, height, RGBA_Down, id]() {
        rect(x, y, width, height, RGBA_Down, id);
    });
    bind(id, "ButtonLeftReleased", [this, x, y, width, height, RGBA_Up, id, func]() {
        rect(x, y, width, height, RGBA_Up, id);
        func();
    });
}


Rendu::~Rendu()
{
	
}