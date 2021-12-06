#include "UI.h"
#include "Game.h"


UI::UI() {
	
	while (true) {
		///1 - закрити гру
		bool exit = 0;

		Font myFont;
		myFont.loadFromFile("../textures_tetris/pixelFont.ttf");
		Text text("1 - 16bit style\n2 - Classic style\n3 - Minimilise style\nESC - exit", myFont, 50);
		text.setPosition(0, 0);
		RenderWindow menuWindow(VideoMode(600, 250), "/MENU/");
		while (menuWindow.isOpen()) {
			Event event;
			while (menuWindow.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					menuWindow.close();
				}
			}
			menuWindow.clear(Color(0, 0, 0, 0));

			menuWindow.draw(text);
			menuWindow.display();
			if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1)) {
				texturePackName = "16bit";
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2)) {
				texturePackName = "classic";
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3)) {
				texturePackName = "min";
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				exit = 1;
				break;
			}
		}
		
		///якщо гравець бажає вийти, виходимо з циклу
		if (exit) {
			break;
		}

		Clock pleaseWait;
		while (pleaseWait.getElapsedTime().asSeconds() <= 0.2) {}//створюємо невелику затримку, аби уникнути випадкового вибору параметрів

		while (menuWindow.isOpen()) {
			Event event;
			while (menuWindow.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					menuWindow.close();
				}
			}
			menuWindow.clear(Color(0, 0, 0, 0));

			text.setString("1 - Easy\n2 - Normal\n3 - Hard\nESC - exit");
			menuWindow.draw(text);
			menuWindow.display();

			if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1)) {
				gameSpeedCoef = 1;
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2)) {
				gameSpeedCoef = 0.8;
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3)) {
				gameSpeedCoef = 0.6;
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				exit = 1;
				break;
			}
		}

		if (exit) {
			break;
		}

		pleaseWait.restart();
		while (pleaseWait.getElapsedTime().asSeconds() <= 0.2) {}
		
		while (menuWindow.isOpen()) {
			Event event{};
			while (menuWindow.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					menuWindow.close();
				}
			}
			menuWindow.clear(Color(0, 0, 0, 0));

			text.setString("1 - Classic mode\n2 - Bomb mode\n3 - Absolutely hardcore mode\nESC - exit");
			menuWindow.draw(text);
			menuWindow.display();

			if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1)) {
				gameModeName = "Classic";
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2)) {
				gameModeName = "Bomb";
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3)) {
				gameModeName = "Hardcore";
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				exit = 1;
				break;
			}
		}

		if (!exit) {
			Game game(texturePackName, gameSpeedCoef, gameModeName, &menuWindow, true);
		}
		else {
			break;
		}
	}
}