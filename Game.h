#pragma once
#include "Render.h"
#include "Logic.h"
#include "Figure.h"
#include "HardcoreMode.h"
#include "BombMode.h"
#include "cmath"
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

using std::map;
using std::string;
using std::pair;
using namespace sf;

/**
 * \class Game Головний клас гри, об'єднує в собі всі дані та поєднує методи в одну програму
 */
class Game
{
protected:
	Render* _render_ = nullptr;//!<включає в себе логіку відображення
	Logic* _logic_ = nullptr;//!<містить в собі функції логіки гри
	Figure* _figure_ = nullptr;
	vector<vector<pair<bool, string>>>* field = new vector < vector<pair<bool, string>>>;//!<ігрове поле
	
	long unsigned int scores = 0;
	double speedCoef;

	bool tryMoveRight();
	bool tryMoveLeft();

	void mainGame(RenderWindow* gameWindow);

	void tryRotateFigure();

public:
	Logic* getLogic();
	vector<vector<pair<bool, string>>>* getField();
	Game(string texturePackName, double _speedCoef, string gameMode, RenderWindow* gameWindow, bool needStartGame);
	~Game();
};

