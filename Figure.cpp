#include "Figure.h"


void Figure::setX (int newX){
	this->x = newX;
}

void Figure::setY (int newY){
	this->y = newY;
}

vector <int> Figure::getFigureCoords (){
	return figureCoords;
}

int Figure::getRotationPos (){
	return rotationPos;
}

int Figure::getFigureID (){
	return this->figureID;
}

/**
 * можна використати для перевірки існування фігури всередині списку в режимах, де масив фігур змінюється під час гри
 * @return вектор усіх існуючих фігур
 */
vector <vector <int>> Figure::getFigures (){
	return figures;
}

int Figure::getX (){
	return x;
}

int Figure::getY (){
	return y;
}

string Figure::getColor (){
	return currentColor;
}



/**
 * задаємо нову фігуру, яка не дорівнює минулій, використовуючи систему псевдовипадкових чисел
 * @param figureID айді минулої фігури, використовується для того, щоб уникнути повторення фігур
 */
void Figure::newFigure (const int figureID){
	vector <vector <int>> figureS;
	figureS = getFigures();
	int randInt;
	do {
		randInt = randomNumber(&figureProbs);
	} while ( randInt == getFigureID());
	this->figureCoords = figureS[randInt];
	this->figureID = randInt;
	rotationPos = 0;
	y = 0;
	x = 4;
	//задаємо новий колір фігурі
	setRandomColor(this->currentColor);
}


/**
 * задаємо фігурі випадковий колір з використанням системи псевдовипадкових чисел
 */
void Figure::setRandomColor (string currentColor){
	const string colors[5] = {"blue", "green", "orange", "red", "yellow"};
	string newColor;
	do {
		newColor = colors[randomNumber(&colorProbs)];
	} while ( newColor == currentColor );
	this->currentColor = newColor;
}


void Figure::createBomb (){
	this->figureCoords = {1, 2, 5, 6, 1, 2, 5, 6, 1, 2, 5, 6, 1, 2, 5, 6};
	this->figureID = 7;
	rotationPos = 0;
	y = 0;
	x = 4;
}


void Figure::rotateFigure (){
	this->rotationPos++;
	if (this->rotationPos > 3) {
		this->rotationPos = 0;
	}
}


/**
 * функція оберненого повороту, використовується коли поворот неможливий
 */
void Figure::reverseRotate (){
	this->rotationPos--;
	if (this->rotationPos < 0) {
		rotationPos = 3;
	}
}


/**
 * створюємо базові фігури, встановлюємо вірогідності кольорів та фігур в початкове положення
 */
Figure::Figure (){
	figures.resize(7);
	figures[0] = {1, 5, 9, 13,  4, 5, 6, 7,   2, 6, 10, 14,   8, 9, 10, 11};//I
	figures[1] = {1, 5, 6, 10,  5, 6, 8, 9,   1, 5, 6, 10,    5, 6, 8, 9};  //5
	figures[2] = {2, 5, 6, 9,   4, 5, 9, 10,  2, 5, 6, 9,     4, 5, 9, 10}; //2
	figures[3] = {9, 10, 6, 2,  1, 5, 6, 7,   2, 3, 6, 10,    5, 6, 7, 11}; //J
	figures[4] = {1, 5, 9, 10,  4, 5, 6, 8,   0, 1, 5, 9,     2, 4, 5, 6};  //L
	figures[5] = {2, 5, 6, 10,  2, 5, 6, 7,   2, 6, 7, 10,    5, 6, 7, 10}; //T
	figures[6] = {1, 2, 5, 6,   1, 2, 5, 6,   1, 2, 5, 6,     1, 2, 5, 6};  //o
	
	figureProbs.resize(figures.size());
	for (int i = 0; i < figureProbs.size(); i++) {
		figureProbs[i] = 30;
	}
	
	colorProbs.resize(5);
	for (int i = 0; i < colorProbs.size(); i++) {
		colorProbs[i] = 30;
	}
}


/**
 * функція додавання нової фігури, також перевіряється правильність розміру фігури
 */
void Figure::newFigure (vector <int> NEW_FIGURE){
	if (NEW_FIGURE.size() % 4 == 0 && !NEW_FIGURE.empty()) {
		figures.push_back(NEW_FIGURE);
		figureProbs.push_back(30);
	}
}


/**
 * система псевдовипадкових чисел, схожа на ту, яка реалізована в грі DOTA, але адаптована під більшу кількість подій.
 * вірогідність випадіння обраного числа зменшується вдвічі та розподілюється між вірогідностями інших подій
 * @param probabilities вектор вірогідностей
 * @return випадкове число, яке знаходиться в межах від нуля до розміру вектора невключно
 */
int Figure::randomNumber (vector <double> *probabilities){
	int randInt = rand() % ((*probabilities).size() * 30);
	int num;
	int sum = 0;
	for (int i = 0; i < (*probabilities).size(); i++) {
		sum += (*probabilities)[i];
		if (randInt <= sum) {
			num = i;
			(*probabilities)[i] *= 0.5;
			for (int k = 0; k < (*probabilities).size(); k++) {
				if (i != k) {
					(*probabilities)[k] += (*probabilities)[i] / ((*probabilities).size() - 1);
				}
			}
			break;
		}
	}
	return num;
}