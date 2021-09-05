#pragma once
#include "Background.h"
#include "Board.h"

using namespace std;
using namespace sf;

class Button {
private:
	Texture buttonTexture;
	Sprite button;
	Text buttonText;
	Font buttonFont;
public:
	Button() { }
	void loadImageButton(String filename) {
		if (!buttonTexture.loadFromFile(filename)) {
			cout << "Could not load button file";
		}
		button.setTexture(buttonTexture);
	}
	//Text related
	void setText(String text) {
		buttonText.setString(text);
	}
	void setFont(String fontPath) {
		if (!buttonFont.loadFromFile(fontPath)) {
			cout << "Could not load font file";
			return;
		}
		buttonText.setFont(buttonFont);
	}
	void setFontSize(int size) {
		buttonText.setCharacterSize(size);
	}
	Text getText() {
		return buttonText;
	}
	void setTextPosition(int x, int y) {
		buttonText.setPosition(x, y);
	}
	//End

	void setTexture(String filename) {
		if (!buttonTexture.loadFromFile(filename)) {
			cout << "Could not load button file";
		}
		button.setTexture(buttonTexture);
	}
	void setPosition(int x, int y) {
		button.setPosition(x, y);
	}
	Sprite getButton() {
		return button;
	}
	void draw(RenderWindow &window) {
		window.draw(button);
		window.draw(buttonText);
	}
	bool isClicked(int mouseX, int mouseY) {
		return button.getGlobalBounds().contains(mouseX, mouseY);
	}
};

enum GameState {
	MAINMENU,
	MAINGAME,
	EXIT,
	PAUSE,
	GAMEOVER
};

class CGame {
private:
	GameState _gameState;
	Button _playButton, _exitButton;
	SoundBuffer _clickedSoundBuffer;
	Sound _clicked;
	Music _backgroundMusic;

	//For cursor changing settings
	View fixed;
	Texture _cursorTexture;
	Sprite _cursor;

	//Custom Classes
	Background background;
	CBoard _board;
	
	//Measurements
	Clock _frameClock;
	int width;
	int height;

	Texture _GMture;
	Texture _Pauseture;
	Texture _GOture;
	Sprite _GMText;
	Sprite _PauseText;
	Sprite _GOText;
public:
	CGame() {
		width = 1280;
		height = 720;
		_gameState = GameState::MAINMENU;
		_playButton.loadImageButton("assets/images/green_button04.png");
		_playButton.setFont("assets/fonts/kenvector_future.ttf");
		_playButton.setFontSize(48);
		_playButton.setPosition((width / 2) - 125, (height / 2) - 64 - 32 + 200);
		_playButton.setText("Play");
		_playButton.setTextPosition((width / 2) - 125 + 50, (height / 2) - 64 - 32 - 5 + 200);

		_exitButton.loadImageButton("assets/images/green_button04.png");
		_exitButton.setFont("assets/fonts/kenvector_future.ttf");
		_exitButton.setFontSize(48);
		_exitButton.setPosition((width / 2) - 125, (height / 2) - 64 + 64 + 200);
		_exitButton.setText("Exit");
		_exitButton.setTextPosition((width / 2) - 125 + 60, (height / 2) - 64 + 64 - 5 + 200);

		if (!_clickedSoundBuffer.loadFromFile("assets/sound/click1.ogg")) {
			cout << "Could not load clicked sound file" << endl;
		}
		_clicked.setBuffer(_clickedSoundBuffer);

		if (!_backgroundMusic.openFromFile("assets/music/Machine in the Walls.ogg")) {
			cout << "Could not load background music file" << endl;
		}

		//Menu texts
		if (!_GMture.loadFromFile("assets/images/text/title.png")) {
			cout << "Cannot open board image file." << endl;
		}
		_GMText.setTexture(_GMture);
		_GMText.setPosition(140, 25);

		if (!_Pauseture.loadFromFile("assets/images/text/pause.png")) {
			cout << "Cannot open board image file." << endl;
		}
		_PauseText.setTexture(_Pauseture);
		_PauseText.setPosition(302, 100);

		if (!_GOture.loadFromFile("assets/images/text/gameover.png")) {
			cout << "Cannot open board image file." << endl;
		}
		_GOText.setTexture(_GOture);
		_GOText.setPosition(140, 50);

		_cursorTexture.loadFromFile("assets/images/cursor.png");
		_cursor.setTexture(_cursorTexture);
		_cursor.setOrigin(32, 32);
	}

	//START Game function
	void start() {
		RenderWindow window(VideoMode(width, height), "Zombie Invasion");
		
		_backgroundMusic.play();
		_backgroundMusic.setVolume(30);

		while (window.isOpen()) {
			if (_gameState == GameState::MAINMENU) {
				window.setMouseCursorVisible(true);
				mainMenu(window);
			}
			else if (_gameState == GameState::MAINGAME) {
				mainGame(window);
			}
			else if (_gameState == GameState::EXIT) {
				window.setMouseCursorVisible(true);
				window.close();
			}
			else if (_gameState == GameState::PAUSE) {
				window.setMouseCursorVisible(true);
				pause(window);
			}
			else if (_gameState == GameState::GAMEOVER) {
				window.setMouseCursorVisible(true);
				gameover(window);
			}
		}
	}

	void mainMenu(RenderWindow &window) {
		//Event Handling
		Event event;
		
		while (window.pollEvent(event)) {
			// Ketika menekan tombol close
			if (event.type == Event::Closed) {
				window.close();
			}

			// Mouse dilepas setelah diklik
			if (event.type == Event::MouseButtonReleased) {
				if (_playButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
					_playButton.loadImageButton("assets/images/green_button04.png");
					_clicked.play();
					_gameState = GameState::MAINGAME;
				}
				if (_exitButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
					_exitButton.loadImageButton("assets/images/green_button04.png");
					_clicked.play();
					_gameState = GameState::EXIT;
				}
			}
			// Mouse saat diklik
			if (event.type == Event::MouseButtonPressed) {
				if (_playButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
					_playButton.loadImageButton("assets/images/green_button03.png");
				}
				if (_exitButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
					_exitButton.loadImageButton("assets/images/green_button03.png");
				}
			}
		}
		//Draw Objects
		window.clear();
		background.drawMainBG(window);
		window.draw(_GMText);
		_playButton.draw(window);
		_exitButton.draw(window);
		window.display();
	}

	void mainGame(RenderWindow& window) {
		//Setting cursor
		window.setMouseCursorVisible(false);
		fixed = window.getView();

		_cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
		
		//Stuffs
		Time frameTime = _frameClock.restart();
		
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonReleased) {
				_board.Shoot(event);
			}
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::P) {
					_gameState = GameState::PAUSE;
					break;
				}
				if (event.key.code == Keyboard::R) {
					_board.Reload();
				}
			}
		}

		if (!_board.checkHP()) {
			_gameState = GameState::GAMEOVER;
			return;
		}

		//Draw Objects
		window.clear();
		window.setView(fixed);
		background.drawBackground(window);

		_board.spawn(window, frameTime.asSeconds(), frameTime);
		_board.drawTowermv(window, frameTime);
		_board.towerDraw(window);
		_board.statDraw(window);
		_board.RCD(frameTime.asSeconds());

		window.draw(_cursor);
		
		window.display();
	}

	void pause(RenderWindow& window) {
		//pause menu
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::P) {
					_gameState = GameState::MAINGAME;
					break;
				}
			}
		}

		window.clear();
		background.drawMainBG(window);
		window.draw(_PauseText);
		window.display();
	}

	void gameover(RenderWindow& window) {
		//gameover menu
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::MouseButtonReleased) {
				_gameState = GameState::MAINMENU;
				_board.reset();
			}
		}

		window.clear();
		background.drawMainBG(window);
		window.draw(_GOText);
		window.display();
	}
};