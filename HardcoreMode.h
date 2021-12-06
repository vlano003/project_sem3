#pragma once
#include "Render.h"

class HardcoreMode : public Render
{
public:
	HardcoreMode(RenderWindow* _gameWindow, string textureName, int x, int y, bool needStart) :Render(_gameWindow, textureName, x, y, needStart) {};
	void drawAll(int BG_X, int BG_Y, vector<vector <pair <bool, string> > >* field, vector<int> figure, int figureX, int figureY, string figureColor, int rotCode, int scores)override;
};