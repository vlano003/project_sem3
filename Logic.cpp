#include "Logic.h"

Logic::Logic (int _fieldSizeX, int _fieldSizeY){
	this->x = _fieldSizeX;
	this->y = _fieldSizeY;
}


const int Logic::getX (){
	return x;
}


const int Logic::getY (){
	return y;
}


/**
 * @return 1 - колізія відбулась, 0 - ні
 */
bool Logic::yCollision (vector <int> figure, int x_, int y_, vector <vector <pair <bool, string>>> *field, int rotationID){
	for (int i = (figure.size() / 4) * rotationID; i < ((figure.size() / 4) * rotationID) + (figure.size() / 4); i++) {
		int yf_ = figure[i] / 4;
		int xf_ = figure[i] % 4;
		///перевірка задля запобігання виходу за поле
		if (yf_ + y_ + 1 < getY() && (yf_ + y_) >= 0) {
			///перевірка на колізію
			if ((*field)[yf_ + y_ + 1][xf_ + x_].first) {
				return 1;
			}
		}else {
			return 1;
		}
	}
	return 0;
}


/**
 * @param bias сдвиг за Х
 * @return 1 - колізія відбулась, 0 - ні
 */
bool Logic::xCollision (vector <int> figure, int x_, int y_, vector <vector <pair <bool, string>>> *field, int bias, int rotationID){
	for (int i = ((figure.size() / 4) * rotationID); i < ((figure.size() / 4) * rotationID) + (figure.size() / 4); i++) {
		int yf_ = figure[i] / 4;
		int xf_ = figure[i] % 4;
		
		///перевірка задля запобігання виходу за поле
		if ((yf_ + y_) < getY() && (yf_ + y_) >= 0 && xf_ + x_ + bias < getX() && xf_ + x_ + bias >= 0) {
			///пеервірка на коліію
			if ((*field)[yf_ + y_][xf_ + x_ + bias].first) {
				return 1;
			}
		}else {
			return 1;
		}
	}
	return 0;
}


void Logic::saveFigure (vector <int> figure, int figureX, int figureY, string color, vector <vector <pair <bool, string>>> *field, int rotationID){
	for (int i = ((figure.size() / 4) * rotationID); i < ((figure.size() / 4) * rotationID) + (figure.size() / 4); i++) {
		(*field)[figure[i] / 4 + figureY][figure[i] % 4 + figureX].first = 1;
		(*field)[figure[i] / 4 + figureY][figure[i] % 4 + figureX].second = color;
	}
}


/**
 * видаляє заповнені лінії
 * @return кількість знищених ліній
 */
int Logic::destroyFullLines (vector <vector <pair <bool, string>>> *field){
	int destroyedLines = 0;
	for (int i = 0; i < (*field).size(); i++) {
		bool isFull = 1;
		for (int k = 0; k < (*field)[i].size(); k++) {
			if (!(*field)[i][k].first) {
				isFull = 0;
				break;
			}
		}
		if (isFull) {
			destroyedLines++;
			for (int k = i; k > 1; k--) {
				(*field)[k] = (*field)[k - 1];
			}
			i--;
		}
		
	}
	return destroyedLines;
}


/**
 * @return 1 - гра закінчилась (щойно створена фігура дає колізію), 0 - гра продовжується
 */
bool Logic::checkEnd (vector <vector <pair <bool, string>>> *field, vector <int> figure, int x_){
	for (int i = 0; i < 4; i++) {
		if ((*field)[3][figure[i] / 4 + x_].first) {
			return 1;
		}
	}
	return 0;
}


/**
 * математичка функція, використовується при обчисленні очок
 */
short int Logic::sgn (int x){
	if (x > 0) {
		return 1;
	}else if (x < 0) {
		return -1;
	}else {
		return 0;
	}
}


bool Logic::getBomb (){
	return false;
}
