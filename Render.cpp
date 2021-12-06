#include "Render.h"

/**
 * завантажуємо необхідні текстури, ресайзимо вікно
 * @param x ширина ігрового поля
 * @param y висота ігрового поля
 * @param createWindow 1 - необхідно створювати вікно, 0 - ні
 */
Render::Render (RenderWindow *_gameWindow, const string& texturePackName, int x, int y, bool createWindow) {
	gameWindow = _gameWindow;
	Texture texture;
	map < string, string > texturePath = getTexturesPaths(texturePackName);
	background.loadFromFile( texturePath["black"] );
	
	texture.loadFromFile( texturePath["blue"] );
	textures.insert( pair < string, Texture >( "blue", texture ));
	
	texture.loadFromFile( texturePath["green"] );
	textures.insert( pair < string, Texture >( "green", texture ));
	
	texture.loadFromFile( texturePath["orange"] );
	textures.insert( pair < string, Texture >( "orange", texture ));
	
	texture.loadFromFile( texturePath["red"] );
	textures.insert( pair < string, Texture >( "red", texture ));
	
	texture.loadFromFile( texturePath["yellow"] );
	textures.insert( pair < string, Texture >( "yellow", texture ));
	
	pixelFont.loadFromFile( "../textures_tetris/pixelFont.ttf" );
	if (createWindow) {
		gameWindow->create( VideoMode((x + 4) * 24.f, y * 24.f ), "/TETRIS/" );
	} else {
		gameWindow->close();
	}
}


/**
 * @return шляхи до необхідних текстур з обраного паку
 */
map < string, string > Render::getTexturesPaths (const string& texturePackName) {
	const map < string, string > textures_16bit = {{"black",  "../textures_tetris\\16bit_style\\texture_sq_black.png"},
												   {"blue",   "../textures_tetris\\16bit_style\\texture_sq_blue.png"},
												   {"green",  "../textures_tetris\\16bit_style\\texture_sq_green.png"},
												   {"orange", R"(..\textures_tetris\16bit_style\texture_sq_orange.png)"},
												   {"red",    R"(..\textures_tetris\16bit_style\texture_sq_red.png)"},
												   {"yellow", R"(..\textures_tetris\16bit_style\texture_sq_yellow.png)"}
	},
			
			textures_classic = {{"black",  "../textures_tetris\\classic_style\\texture_sq_black.png"},
								{"blue",   "../textures_tetris\\classic_style\\texture_sq_blue.png"},
								{"green",  "../textures_tetris\\classic_style\\texture_sq_green.png"},
								{"orange", "../textures_tetris\\classic_style\\texture_sq_orange.png"},
								{"red",    "../textures_tetris\\classic_style\\texture_sq_red.png"},
								{"yellow", "../textures_tetris\\classic_style\\texture_sq_yellow.png"}
	},
			
			textures_min = {{"black",  "../textures_tetris\\min_style\\texture_sq_black.png"},
							{"blue",   "../textures_tetris\\min_style\\texture_sq_blue.png"},
							{"green",  "../textures_tetris\\min_style\\texture_sq_green.png"},
							{"orange", "../textures_tetris\\min_style\\texture_sq_orange.png"},
							{"red",    "../textures_tetris\\min_style\\texture_sq_red.png"},
							{"yellow", "../textures_tetris\\min_style\\texture_sq_yellow.png"}
	};
	if (texturePackName == "min") {
		return textures_min;
	}
	if (texturePackName == "16bit") {
		return textures_16bit;
	}
	///за замовчуванням повертаємо класичні текстури
	return textures_classic;
}


void Render::renderBackground (int fieldSizeX, int fieldSizeY) {
	Sprite BGsprite( background );
	BGsprite.setTextureRect( IntRect(0, 0, 24 * fieldSizeX, 24 * fieldSizeY ));
	gameWindow->draw( BGsprite );
}


void Render::renderField (vector < vector < pair < bool, string>> > *field) {
	for (int i = 0; i < (*field).size(); i++) {
		for (int k = 0; k < (*field)[i].size(); k++) {
			if ((*field)[i][k].first) {
				Sprite blockSprite( textures[(*field)[i][k].second] );
				blockSprite.setPosition( k * 24.f, i * 24.f );
                gameWindow->draw( blockSprite );
			}
		}
	}
}


void Render::renderFigure (vector < int > figure, int x, int y, string color, int rotationID) {
	auto *figureSprite = new Sprite[figure.size() / 4];
	for (int i = 0; i < 4; i++) {
		figureSprite[i].setTexture( textures[color] );
	}
	for (int i = ((figure.size() / 4) * rotationID); i < ((figure.size() / 4) * rotationID) + (figure.size() / 4); i++) {
		figureSprite[i % 4].setPosition((figure[i] % 4 + x) * 24.f, (figure[i] / 4 + y) * 24.f );
		gameWindow->draw( figureSprite[i % 4] );
	}
}


/**
 * @param x_ ширина поля
 */
void Render::drawScores (int scores, int x_) {
	Text text( std::to_string( scores ), pixelFont, 45 );
	text.setPosition((x_ + 1) * 24, 40 );
	gameWindow->draw( text );
}


/**
 * функція, яка перевіряє, чи нажата ESC. якщо так, викликає паузу
 * @param BG_X ширина поля
 */
void Render::checkPause (int BG_X) {
	if (Keyboard::isKeyPressed( Keyboard::Escape )) {
		///очищуємо вікно, аби гравець не мав можливості бачити поле під час паузи
		gameWindow->clear( Color( 0, 0, 0, 0 ));
		Text textPause( "PAUSE", pixelFont, 100 );
		textPause.setPosition( 112, 50 );
		gameWindow->draw( textPause );
		gameWindow->display();
		Clock pleaseWait;
		while ( pleaseWait.getElapsedTime().asSeconds() <= 0.2 ) {}
		textPause.setPosition( BG_X * 12 + 40, 50 );
		///чекаємо, доки гравець не захоче вийти з паузи
		while ( !(Keyboard::isKeyPressed( Keyboard::Escape ))) {}
		///трьохсекундний таймер виходу з паузи
		for (int i = 3; i >= 1; i--) {
			textPause.setString( std::to_string( i ));
			gameWindow->clear( Color( 0, 0, 0, 0 ));
			gameWindow->draw( textPause );
			gameWindow->display();
			pleaseWait.restart();
			while ( pleaseWait.getElapsedTime().asSeconds() <= 1 ) {}
		}
	}
}


/**
 * в правильному порядку рендерить гри
 */
void Render::drawAll (int BG_X, int BG_Y, vector < vector < pair < bool, string>> > *field, vector < int > figure, int figureX, int figureY, string figureColor, int rotCode, int scores) {
    renderBackground(BG_X, BG_Y);
	renderField(field);
	renderFigure(figure, figureX, figureY, figureColor, rotCode);
	drawScores( scores, BG_X );
	gameWindow->display();
}


/**
 * сповіщуємо гравця, що гра закінчена, НЕ очищуємо вікно, аби гравець мав можливість бачити поле та свої очки
 */
void Render::end () {
	Text text( "Game Over\nPress ENTER\n  or SPACE\n\tto exit", pixelFont, 75 );
	text.setPosition( 20, 80 );
	gameWindow->draw( text );
	gameWindow->display();
	while ( !(Keyboard::isKeyPressed( Keyboard::Enter ) || Keyboard::isKeyPressed( Keyboard::Space ))) {}
	gameWindow->close();
}


