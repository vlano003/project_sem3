#include "HardcoreMode.h"


/**
 * змінює реалізацію, при якій не відображається поле
 */
void HardcoreMode::drawAll(int BG_X, int BG_Y, vector<vector<pair<bool, string>>>* field, vector<int> figure, int figureX, int figureY, string figureColor, int rotCode, int scores)
{
	renderBackground(BG_X, BG_Y);
	renderFigure(figure, figureX, figureY, figureColor, rotCode);
	drawScores(scores, BG_X);
}
