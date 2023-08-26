#pragma once

#include "Base/Base.h"
#include <string>

class Rendu : public Base
{
public:
	Rendu();
	~Rendu();

	int ButtonRect(int x, int y, int width, int height, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()>);
	int ButtonRect(int x, int y, int width, int height, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()>, int id);
	int ButtonRectBorder(int x, int y, int width, int height, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>);
	int ButtonRectBorder(int x, int y, int width, int height, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>, int id);
	int ButtonCircle(int x, int y, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()>);
	int ButtonCircle(int x, int y, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()>, int id);
	int ButtonCircleBorder(int x, int y, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>);
	int ButtonCircleBorder(int x, int y, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>, int id);
	int ButtonRectCircleAngle(int x, int y, int width, int height, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()>);
	int ButtonRectCircleAngle(int x, int y, int width, int height, int radius, unsigned char fillDown[4], unsigned char fillUp[4], std::function<void()>, int id);
	int ButtonRectCircleAngleBorder(int x, int y, int width, int height, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>);
	int ButtonRectCircleAngleBorder(int x, int y, int width, int height, int radius, int border, unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>, int id);

	int ButtonRectCircleAngleBorderWithText(int x, int y, int width, int height, int radius, int border, std::string, int size, unsigned char textDown[4],unsigned char textUp[4],unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>);
	int ButtonRectCircleAngleBorderWithText(int x, int y, int width, int height, int radius, int border, std::string, int size, unsigned char textDown[4],unsigned char textUp[4],unsigned char fillDown[4], unsigned char fillUp[4], unsigned char borderDown[4], unsigned char borderUp[4], std::function<void()>, int id);
};