#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <map>
#include <cstring>
#include <utility>
#include <fstream>

class Base
{
public:
	Base();

	bool init(int, int, sf::Uint8*, sf::Uint16*,std::map<int, std::map<std::string,std::function<void()>>>*, bool*);

	~Base();

public:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

	int id = 0;
	bool* screenModified;

    sf::Uint8* matrix;
	sf::Uint16* id_matrix;
	sf::Uint32 convertColor(unsigned char [4]);
	
	std::map<int, std::map<std::string,std::function<void()>>>* map_event;

public:
	int rect(int, int, int, int, unsigned char[4], int);
	int rectBorder(int, int, int, int, int, unsigned char[4], unsigned char[4]);
	int circle(int, int, int, unsigned char[4], int);
	int circleBorder(int, int, int, int, unsigned char[4], unsigned char[4]);
	int rectCircleAngle(int, int, int, int, int, unsigned char[4], int);
	int rectCircleAngleBorder(int, int, int, int, int, int, unsigned char[4], unsigned char[4]);

	int text(int, int, std::string, unsigned short int, unsigned char [4], unsigned char [4], int);

public:
	std::map<int,std::map<const char,std::string>>* font_dictionnary = new std::map<int,std::map<const char,std::string>>;
	const char* character_list[95] = {
		" ","!","\"","#","$","%","&","'","(",")","*","+",",","-",".",
		"/","0","1","2","3","4","5","6","7","8","9",":",";","<","=",
		">","?","@","A","B","C","D","E","F","G","H","I","J","K","L",
		"M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","[",
		"\\","]","^","_","`","a","b","c","d","e","f","g","h","i","j",
		"k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","{","|","}","~"
	};
	std::string convertText(unsigned char, unsigned short int);

public:
	void bind(int id, std::string event, std::function<void()> func);
};