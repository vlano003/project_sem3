#pragma once
#include <iostream>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
using std::string;
using std::map;
using namespace sf;

/**
 * \class UI клас юзер інтерфейсу, може викликати початок гри
 */
class UI
{
	string texturePackName;
	double gameSpeedCoef;
	string gameModeName;
public:
	UI();
};

