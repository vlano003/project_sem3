#pragma once
#include <vector>
#include <string>

using std::pair;
using std::string;
using std::vector;


/**
 * \class Logic містить в собі фукнції обробки та зміни поля та фігури
 */
class Logic
{
	int x = 10;//!<розмір поля за Х
	int y = 20;//!<розмір поля за Y
public:
	const int getX();
	const int getY();
	
	bool yCollision(vector<int> figure, int x_, int y_, vector<vector <pair <bool, string> > >* field, int rotationID);//!<функція перевірки вертикальної колізії
	bool xCollision(vector<int> figure, int x_, int y_, vector<vector <pair <bool, string> > >* field, int bias, int rotationID);//!<фукнція перевірки горизонтальної колізії

	virtual void saveFigure(vector<int> figure, int figureX, int figureY, string color, vector<vector <pair <bool, string> > >* field, int rotationID);

	virtual int destroyFullLines(vector<vector <pair <bool, string> > >* field);
	bool checkEnd(vector<vector <pair <bool, string> > >* field, vector<int> figure, int x_);//!<функція перевірки на кінець гри

	short int sgn(int x);
	
	virtual bool getBomb();

	Logic(int _fieldSizeX, int _fieldSizeY);

};

