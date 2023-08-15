#pragma once

#include "Base/Base.h"

class Rendu: public Base
{
public:
	Rendu();
	~Rendu();

	void Button(int, int, int, int, unsigned char [4], unsigned char [4], std::function<void()>);
};