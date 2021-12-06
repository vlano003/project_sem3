#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;
using std::pair;

using namespace sf;

/**
 * \class Render класс рендеру. відображає поле, фігури та кількість очок, містить функції юзер інтерфейсу
 */
class Render
{
protected:

	Font pixelFont;
	map<string, Texture> textures;
	Texture background;
	RenderWindow* gameWindow;//!<ігрове вікно
	
	static map<string, string> getTexturesPaths(const string& texturePackName);
public:
	void renderBackground(int fieldSizeX, int fieldSizeY);
	void renderField(vector<vector <pair <bool, string> > >* field);
	void renderFigure(vector<int> figure, int x, int y, string color, int rotationID);
	void drawScores(int scores, int x_);
	void checkPause(int BG_X);

	virtual void drawAll(int BG_X, int BG_Y, vector<vector <pair <bool, string> > >* field, vector<int> figure, int figureX, int figureY, string figureColor, int rotCode, int scores);

	void end();

	Render(RenderWindow* _gameWindow, const string& texturePackName, int x, int y, bool needRenderWindow);
};

