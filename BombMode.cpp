#include "BombMode.h"


/**
 * додаємо обробку бомби до функції збереження, аби не змінювати код всередині Game
 */
void BombMode::saveFigure(vector<int> figure, int figureX, int figureY, string color, vector<vector<pair<bool, string>>>* field, int rotationID)
{
	///якщо фігура не бомба, зберігаємо її
	if (!isBomb) {
		for (int i = ((figure.size() / 4) * rotationID); i < ((figure.size() / 4) * rotationID) + (figure.size() / 4); i++) {
			(*field)[figure[i] / 4 + figureY][figure[i] % 4 + figureX].first = 1;
			(*field)[figure[i] / 4 + figureY][figure[i] % 4 + figureX].second = color;
		}
	}
	///інакше викликаємо функцію детонації бомби
	else {
		bombDetonate(field, figure, figureX, figureY);
	}
}


/**
 * функція детонації бомби, працює за принципом бомби з bomberman
 */
void BombMode::bombDetonate(vector<vector<pair<bool, string>>>* field, vector<int> figure, int x_, int y_)
{
	int figureCoordX, figureCoordY;
	for (int i = 0; i < 4; i += 3) {
		figureCoordX = figure[i] % 4 + x_;
		figureCoordY = figure[i] / 4 + y_;
		for (int m = 0; m < getY(); m++) {
			(*field)[m][figureCoordX].first = 0;
		}
		for (int l = figureCoordY; l > 0; l--) {
			(*field)[l] = (*field)[l - 1];
		}
	}
	isBomb = 0;
}


/**
 * знаходимо та видаляємо заповнені лінії
 * @return кількість знищених ліній
 */
int BombMode::destroyFullLines(vector<vector<pair<bool, string>>>* field)
{
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
	if (destroyedLines >= 2) {
		isBomb = 1;
	}
	return destroyedLines;
}


bool BombMode::getBomb()
{
	return isBomb;
}
