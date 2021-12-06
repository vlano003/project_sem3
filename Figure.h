#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;


class Figure {
	
	short int figureID = 34462;
	vector < int > figureCoords;//!<координати поточної фігури відносно нуля
	short unsigned int rotationPos = 0;
	string currentColor;
	int x;
	int y;
	
	vector < vector < int>> figures;
	
	vector <double> figureProbs;//!<вірогідності випадіння для фігур
	vector <double> colorProbs;//!<вірогідності випадіння для кольорів
	
	void newFigure (vector < int > NEW_FIGURE);//!<додає нову фігуру у вектор фігур
	
public:
	vector < vector < int>> getFigures ();
	
	void setX (int newX);
	
	void setY (int newY);
	
	void newFigure (const int figureID);//!<створює нову фігуру
	
	void setRandomColor (string currentColor);//!<обирає новий колір для фігури
	
	vector < int > getFigureCoords ();
	
	int getRotationPos ();
	
	int getX ();
	
	int getY ();
	
	string getColor ();
	
	void createBomb ();
	
	void rotateFigure ();
	
	void reverseRotate ();
	
	int getFigureID ();
	
	int randomNumber(vector<double>* probabilities);//!<функція псевдовипадкових чисел
	
	Figure ();
};

