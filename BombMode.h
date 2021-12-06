#pragma once
#include "Logic.h"

/**
 * \class містить логіку для режиму BOMB, існує задля того, аби не було необхідності змінювати код класу Game
 */
class BombMode : public Logic
{
	bool isBomb = 0;
	
	void saveFigure(vector<int> figure, int figureX, int figureY, string color,
				 vector<vector <pair <bool, string> > >* field, int rotationID) override;//!<детонує бомбу або зберігає фігуру
	
	void bombDetonate(vector<vector <pair <bool, string> > >* field, vector<int> figure, int x_, int y_);
	
	int destroyFullLines(vector<vector <pair <bool, string> > >* field)override;
public:
	bool getBomb()override;
	
	BombMode(int _x, int _y) :Logic(_x, _y) {};
};

