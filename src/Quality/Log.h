#pragma once
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <sys/resource.h>

class Log
{
private:
	static Log *instance;
	unsigned long int saveTime;
	unsigned long int saveUserTimeUs;
	unsigned long int saveSysTimeUs;
	std::ofstream logFile;
	Log();
	std::string ramValueRefactoring(unsigned long int);
	std::string timeValueRefactoring();

public:
	static Log *getInstance();
	bool logMessage(std::string, std::string);
	~Log();
};