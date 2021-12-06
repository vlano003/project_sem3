#include "Game.h"

/**
 * якщо можливо, сдвигає фігуру вправо
 * @return 1 - фігуру сдвинуто, 0 - ні
 */
bool Game::tryMoveRight()
{
	if (_figure_->getX() != _figure_->getX() - 2) {
		if (!_logic_->xCollision(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), field, 1, _figure_->getRotationPos())) {
			_figure_->setX(_figure_->getX() + 1);
			Clock pleaseWait;
			while (pleaseWait.getElapsedTime().asSeconds() <= 0.05) {}
		}
		else {
			_logic_->saveFigure(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), _figure_->getColor(), field, _figure_->getRotationPos());
			return 1;
		}
	}
	return 0;
}


/**
 * якщо можливо, сдвигає фігуру вліво
 * @return 1 - фігуру сдвинуто, 0 - ні
 */
bool Game::tryMoveLeft()
{
	vector<int> currFigure = _figure_->getFigureCoords();
	int rotationCode = _figure_->getRotationPos();
	bool is0x = 0;
	for (int i = ((currFigure.size() / 4) * rotationCode); i < ((currFigure.size() / 4) * rotationCode) + (currFigure.size() / 4); i++) {
		int x_;
		x_ = _figure_->getX() + currFigure[i] % 4;
		if (x_ == 0) {
			is0x = 1;
			break;
		}
	}
	if (!is0x) {
		if (!_logic_->xCollision(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), field, -1, _figure_->getRotationPos())) {
			_figure_->setX(_figure_->getX() - 1);
			Clock pleaseWait;
			while (pleaseWait.getElapsedTime().asSeconds() <= 0.05) {}
		}
		else {
			_logic_->saveFigure(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(),
					   _figure_->getColor(), field, _figure_->getRotationPos());
			return 1;
		}
	}
	return 0;
}


/**
 * головна функція гри, об'єднує весь функціонал, також змінює коефіцієнт швидкості, контролює правильність таймингів
 */
void Game::mainGame(RenderWindow* gameWindow)
{
	_figure_->newFigure(7);
	while (gameWindow->isOpen()) {
		if (!_logic_->getBomb()) {
			_figure_->newFigure(_figure_->getFigureID());
		}
		else {
			_figure_->createBomb();
		}
		Event event;
		while (gameWindow->pollEvent(event))
		{
			if (event.type == Event::Closed) {
				gameWindow->close();
			}
		}
		if (_logic_->checkEnd(field, _figure_->getFigureCoords(), _figure_->getX())) {
			_render_->end();
			break;
		}
		///додатковий коефіцієнт прискорення, змінюється коли гравець натискає на S
		double speedCoef = 1;
		bool stop = 0;
		
		///таймери для правильності таймингів
		Clock clockMoveY, clockMoveWASD;
		float timingMoveY, timingMoveWASD;
		///необхідна для створення затримки фігури, коли та впала задля можливості сдвинути її
		bool timerStarter = 0;
		do {
			timingMoveY = clockMoveY.getElapsedTime().asSeconds();
			timingMoveWASD = clockMoveWASD.getElapsedTime().asSeconds();
			///постійно змінюємо колір бомби
			if (_logic_->getBomb()) {
				if (timingMoveY > 0.2 * speedCoef * speedCoef) {
					_figure_->setRandomColor(_figure_->getColor());
				}
			}
			///повертаємо значення в початкове положення
			speedCoef = 1;
			while (gameWindow->pollEvent(event))
			{
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::A) && timingMoveWASD >= 0.1 * speedCoef) {
						if (tryMoveLeft()) {
							stop = 1;
							break;
						}
						_render_->drawAll(_logic_->getX(), _logic_->getY(), field, _figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), _figure_->getColor(), _figure_->getRotationPos(), scores);
						clockMoveWASD.restart();
					}
					else if (Keyboard::isKeyPressed(Keyboard::D) && timingMoveWASD >= 0.1 * speedCoef) {
						if (tryMoveRight()) {
							stop = 1;
							break;
						}
						_render_->drawAll(_logic_->getX(), _logic_->getY(), field, _figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), _figure_->getColor(), _figure_->getRotationPos(), scores);
						clockMoveWASD.restart();
					}
					else if (Keyboard::isKeyPressed(Keyboard::S)) {
						speedCoef = 0.05;
						_render_->drawAll(_logic_->getX(), _logic_->getY(), field, _figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), _figure_->getColor(), _figure_->getRotationPos(), scores);
					}
					else if (Keyboard::isKeyPressed(Keyboard::W)) {
						tryRotateFigure();
					}
					_render_->checkPause(_logic_->getX());
				}
			}
			gameWindow->clear();
			_render_->drawAll(_logic_->getX(), _logic_->getY(), field, _figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), _figure_->getColor(), _figure_->getRotationPos(), scores);

			if (!_logic_->yCollision(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), field,
									 _figure_->getRotationPos())) {
				if (timingMoveY > 0.4 * speedCoef * speedCoef) {
					_figure_->setY(_figure_->getY() + 1);
					clockMoveY.restart();
				}
			}
			else if (!timerStarter) {
				clockMoveY.restart();
				timingMoveY = 0;
				timerStarter = 1;
			}
			if (stop) {
				break;
			}
		} while ( !_logic_->yCollision(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), field,
									   _figure_->getRotationPos()) || timingMoveY < 0.15);
		if (!stop) {
			_logic_->saveFigure(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), _figure_->getColor(), field, _figure_->getRotationPos());
		}

		int destroyedLines = _logic_->destroyFullLines(field);
		scores += _logic_->sgn(destroyedLines) * 1000 * pow(1.5, destroyedLines - 1) * destroyedLines;
		///з кожною знищеною фігурою пришвидшуємо гру
		speedCoef *= pow(0.95, destroyedLines);
		_render_->drawAll(_logic_->getX(), _logic_->getY(), field, _figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), _figure_->getColor(), _figure_->getRotationPos(), scores);
	}
}


/**
 * повертаємо фігуру, перевіряємо но колізію. якщо зберегти не можливо, перевіряємо на колізію зі сдвигом вправо та вліво.
 * якщо все ще неможливо, відміняємо поворот
 */
void Game::tryRotateFigure()
{
	_figure_->rotateFigure();
	if (_logic_->xCollision(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), field, 0, _figure_->getRotationPos()))
	{
		if (!_logic_->xCollision(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), field, 1, _figure_->getRotationPos())){
			_figure_->setX(_figure_->getX() + 1);
		}
		else if (!_logic_->xCollision(_figure_->getFigureCoords(), _figure_->getX(), _figure_->getY(), field, -1, _figure_->getRotationPos())) {
			_figure_->setX(_figure_->getX() - 1);
		}
		else {
			_figure_->reverseRotate();
		}
	}
}


/**
 * @param needStartGame 1 - необхідно почати гру, 0 - ні. Використовується для тестування
 */
Game::Game(string texturePackName, double _speedCoef, string gameMode, RenderWindow* gameWindow, bool needStartGame)
{
	this->speedCoef = _speedCoef;
	this->_figure_ = new Figure;
	if (gameMode == "Classic" || gameMode == "Bomb") {
		this->_render_ = new Render(gameWindow, texturePackName, 10, 20, needStartGame);
	}
	else {
		this->_render_ = new HardcoreMode(gameWindow, texturePackName, 10, 20, needStartGame);
		this->speedCoef *= 0.3;
	}

	if (gameMode == "Bomb") {
		this->_logic_ = new BombMode(10, 20);
	}
	else {
		this->_logic_ = new Logic(10, 20);
	}

	int x = _logic_->getX();
	int y = _logic_->getY();

	field->resize(y);
	for (int i = 0; i < y; i++) {
		(*field)[i].resize(x);
		for (int k = 0; k < x; k++) {
			(*field)[i][k].first = 0;
		}
	}
	srand(time(NULL));
	if (needStartGame) {
		mainGame( gameWindow );
	}
}


vector < vector < pair < bool, string>> > *Game::getField () {
	return field;
}


/**
 * @return поточний об'єкт класу Logic, використовується для можливої реалізації стратегії та тестування
 */
Logic *Game::getLogic () {
	return _logic_;
}


Game::~Game () {
	delete _figure_;
	delete _logic_;
	delete _render_;
	delete field;
}
