#pragma once
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <sys/resource.h>

class Log
{
public:
	Log();
	~Log();
    bool send(std::string, std::string);
};