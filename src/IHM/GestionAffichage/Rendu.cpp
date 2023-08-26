#include "Rendu.h"

Rendu::Rendu()
{
}

int Rendu::ButtonRect(int x, int y, int width, int height, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()> func)
{
    return ButtonRect(x, y, width, height, fillDown, fillUp, func, 0);
}

int Rendu::ButtonRect(int x, int y, int width, int height, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()> func, int set_id)
{
    if (set_id == 0)
        set_id = rect(x, y, width, height, fillUp);
    else
        rect(x, y, width, height, fillUp, set_id);
    bind(set_id, "ButtonLeftPressed",
         [this, x, y, width, height, fillDown, set_id]()
         {
             rect(x, y, width, height, fillDown, set_id);
         });
    bind(set_id, "ButtonLeftReleased",
         [this, x, y, width, height, fillUp, set_id, func]()
         {
             rect(x, y, width, height, fillUp, set_id);
             func();
         });
    return set_id;
}

int Rendu::ButtonRectBorder(int x, int y, int width, int height, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func)
{
    return ButtonRectBorder(x, y, width, height, border, fillDown, fillUp, borderDown, borderUp, func, 0);
}

int Rendu::ButtonRectBorder(int x, int y, int width, int height, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func, int set_id)
{
    if (set_id == 0)
        set_id = rectBorder(x, y, width, height, border, fillUp, borderUp);
    else
        rectBorder(x, y, width, height, border, fillUp, borderUp, set_id);

    bind(set_id, "ButtonLeftPressed",
         [this, x, y, width, height, border, fillDown, borderUp, set_id]()
         {
             rectBorder(x, y, width, height, border, fillDown, borderUp, set_id);
         });
    bind(set_id, "ButtonLeftReleased",
         [this, x, y, width, height, border, fillUp, borderUp, set_id, func]()
         {
             rectBorder(x, y, width, height, border, fillUp, borderUp, set_id);
             func();
         });
    return set_id;
}

int Rendu::ButtonCircle(int x, int y, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()> func)
{
    return ButtonCircle(x, y, radius, fillDown, fillUp, func, 0);
}

int Rendu::ButtonCircle(int x, int y, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()> func, int set_id)
{
    if (set_id == 0)
        set_id = circle(x, y, radius, fillUp);
    else
        circle(x, y, radius, fillUp, set_id);
    bind(set_id, "ButtonLeftPressed",
         [this, x, y, radius, fillDown, set_id]()
         {
             circle(x, y, radius, fillDown, set_id);
         });
    bind(set_id, "ButtonLeftReleased",
         [this, x, y, radius, fillUp, set_id, func]()
         {
             circle(x, y, radius, fillUp, set_id);
             func();
         });
    return set_id;
}

int Rendu::ButtonCircleBorder(int x, int y, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func)
{
    return ButtonCircleBorder(x, y, radius, border, fillDown, fillUp, borderDown, borderUp, func, 0);
}

int Rendu::ButtonCircleBorder(int x, int y, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func, int set_id)
{
    if (set_id == 0)
        set_id = circleBorder(x, y, radius, border, fillUp, borderUp);
    else
        circleBorder(x, y, radius, border, fillUp, borderUp, set_id);

    bind(set_id, "ButtonLeftPressed",
         [this, x, y, radius, border, fillDown, borderUp, set_id]()
         {
             circleBorder(x, y, radius, border, fillDown, borderUp, set_id);
         });
    bind(set_id, "ButtonLeftReleased",
         [this, x, y, radius, border, fillUp, borderUp, set_id, func]()
         {
             circleBorder(x, y, radius, border, fillUp, borderUp, set_id);
             func();
         });
    return set_id;
}

int Rendu::ButtonRectCircleAngle(int x, int y, int width, int height, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()> func)
{
    return ButtonRectCircleAngle(x, y, width, height, radius, fillDown, fillUp, func, 0);
}

int Rendu::ButtonRectCircleAngle(int x, int y, int width, int height, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()> func, int set_id)
{
    if (set_id == 0)
        set_id = rectCircleAngle(x, y, width, height, radius, fillUp);
    else
        rectCircleAngle(x, y, width, height, radius, fillUp, set_id);

    bind(set_id, "ButtonLeftPressed",
         [this, x, y, width, height, radius, fillDown, set_id]()
         {
             rectCircleAngle(x, y, width, height, radius, fillDown, set_id);
         });
    bind(set_id, "ButtonLeftReleased",
         [this, x, y, width, height, radius, fillUp, set_id, func]()
         {
             rectCircleAngle(x, y, width, height, radius, fillUp, set_id);
             func();
         });
    return set_id;
}

int Rendu::ButtonRectCircleAngleBorder(int x, int y, int width, int height, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func)
{
    return ButtonRectCircleAngleBorder(x, y, width, height, radius, border, fillDown, fillUp, borderDown, borderUp, func, 0);
}

int Rendu::ButtonRectCircleAngleBorder(int x, int y, int width, int height, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func, int set_id)
{
    if (set_id == 0)
        set_id = rectCircleAngleBorder(x, y, width, height, radius, border, fillUp, borderUp);
    else
        rectCircleAngleBorder(x, y, width, height, radius, border, fillUp, borderUp, set_id);

    bind(set_id, "ButtonLeftPressed",
         [this, x, y, width, height, radius, border, fillDown, borderDown, set_id]()
         {
             rectCircleAngleBorder(x, y, width, height, radius, border, fillDown, borderDown, set_id);
         });
    bind(set_id, "ButtonLeftReleased",
         [this, x, y, width, height, radius, border, fillUp, borderUp, set_id, func]()
         {
             rectCircleAngleBorder(x, y, width, height, radius, border, fillUp, borderUp, set_id);
             func();
         });
    return set_id;
}

int Rendu::ButtonRectCircleAngleBorderWithText(int x, int y, int width, int height, int radius, int border, std::string textShow, int size, unsigned char textDown[4], unsigned char textUp[4], unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func)
{
    std::cout << " ---" << x << " ," << y << " ," << width << " ," << height << std::endl;
    return ButtonRectCircleAngleBorderWithText(x, y, width, height, radius, border, textShow, size, textDown, textUp, fillDown, fillUp, borderDown, borderUp, func, 0);
}

int Rendu::ButtonRectCircleAngleBorderWithText(int x, int y, int width, int height, int radius, int border, std::string textShow, int size, unsigned char textDown[4], unsigned char textUp[4], unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()> func, int set_id)
{
    int widthText = getWidthText(textShow, size);
    int xText = x + width / 2 - widthText / 2, yText = y + height / 2 - size / 2;
    if (set_id == 0)
    {
        set_id = rectCircleAngleBorder(x, y, width, height, radius, border, fillUp, borderUp);
        text(xText, yText, textShow, size, textUp, fillUp);
    }
    else
    {
        rectCircleAngleBorder(x, y, width, height, radius, border, fillUp, borderUp, set_id);
        text(xText, yText, textShow, size, textUp, fillUp);
    }

    bind(set_id, "ButtonLeftPressed",
         [this, x, y, xText, yText, width, height, radius, border, fillDown, borderDown, set_id, textShow, size, textDown]()
         {
             rectCircleAngleBorder(x, y, width, height, radius, border, fillDown, borderDown, set_id);
             text(xText, yText, textShow, size, textDown, fillDown);
         });
    bind(set_id, "ButtonLeftReleased",
         [this, x, y, xText, yText, width, height, radius, border, fillUp, borderUp, set_id, func, textShow, size, textUp]()
         {
             rectCircleAngleBorder(x, y, width, height, radius, border, fillUp, borderUp, set_id);
             text(xText, yText, textShow, size, textUp, fillUp);
             func();
         });
    return set_id;
}

Rendu::~Rendu()
{
}