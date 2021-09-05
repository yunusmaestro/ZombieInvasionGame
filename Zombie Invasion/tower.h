#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<string>

class Tower {
private:
	IntRect rectTower;
	Texture _towerTexture;
	Sprite _tower;

	IntRect rectStrike;
	Texture _strikeTexture;
	Sprite _strike;

	int defaulttimer = 18;

	//animator
	double _currentTimeAnimation = 0;
	int frame;
	bool tower = false;
	bool strike = false;

	double _shootTimer = 0;
	int _nextShoot;

	//simpler data-keeping purposes...
	int locationSpawn[5];	// sebenarnya cuma 3, tapi dilebihkan (thunder)
	int location;

	//targeted zombie
	int target = 10;
	int target_x;
public:
	//constructor
	Tower() {
		frame = 0;

		//for tower
		rectTower.left = 0;
		rectTower.top = 0;
		rectTower.width = 105;
		rectTower.height = 277;

		if (!_towerTexture.loadFromFile("assets/images/sprites/tower.png")) {
			cout << "Cannot open board image file." << endl;
		}
		_tower.setTexture(_towerTexture);
		_tower.setTextureRect(rectTower);

		//for strike
		rectStrike.left = 0;
		rectStrike.top = 0;
		rectStrike.width = 276;
		rectStrike.height = 720;

		if (!_strikeTexture.loadFromFile("assets/images/sprites/strike.png")) {
			cout << "Cannot open board image file." << endl;
		}
		_strike.setTexture(_strikeTexture);
		_strike.setTextureRect(rectStrike);
		
		//timer cooldown
		_nextShoot = rand() % 2 + defaulttimer;

		//location spawning y offset (For the thunder)
		locationSpawn[1] = 130;
		locationSpawn[2] = 330;
		locationSpawn[3] = 530;
	}

	bool Move() {
		return tower;
	}

	bool Strike() {
		return strike;
	}

	int getFrame() {
		return frame;
	}

	void setTarget(int _target, int _target_x) {
		target = _target;
		target_x = _target_x;

		int ly = 0 - 720 + locationSpawn[location] + 133;
		
		_strike.setPosition(_target_x - 110, ly);
	}

	int getTarget() {
		return target;
	}

	void cancelStrike() {
		tower = false;
		target = 10;
	}

	//functions
	void setup(int loc) {
		location = loc;
		if (loc == 1) {
			_tower.setPosition(60 + 15, -130);
		}
		else if (loc == 2) {
			_tower.setPosition(60 + 10, 60);	// x nya menurun, karena gambar wallnya miring
		}
		else if (loc == 3) {
			_tower.setPosition(60 + 5, 250);
		}
	}

	void reset() {
		tower = false;
		strike = false;
		frame = 0;
	}

	void moveStart(double deltaTime) {
		_shootTimer += deltaTime;
		if (_shootTimer >= _nextShoot) {
			_shootTimer = 0;
			//cooldown modifier
			_nextShoot = rand() % 2 + defaulttimer;

			tower = true;
		}
	}

	//draw functions
	void drawTower(RenderWindow& window) {
		window.draw(_tower);
	}

	void drawStrike(RenderWindow& window) {
		window.draw(_strike);
	}

	//animations
	//Tower movement
	void toweranimation(double deltaTime) {
		_currentTimeAnimation += deltaTime;
		if (_currentTimeAnimation >= 0.05f) {
			_currentTimeAnimation = 0;

			frame++;
			int x = (frame - 1) % 3;
			int y = (frame - 1) / 3;
			int spriteX = x * 105;
			int spriteY = y * 277;

			rectTower.left = spriteX;
			rectTower.top = spriteY;
			_tower.setTextureRect(rectTower);

			if (frame >= 12) {	// sesuai assets, tower hanya 12 gambar
				frame = 0;
				tower = false;
				strike = true;
			}
		}
	}

	void strikeanimation(double deltaTime) {
		_currentTimeAnimation += deltaTime;
		if (_currentTimeAnimation >= 0.015f) {
			_currentTimeAnimation = 0;

			frame++;
			int x = (frame - 1) % 7;
			int y = (frame - 1) / 7;
			int spriteX = x * 276;
			int spriteY = y * 720;

			rectStrike.left = spriteX;
			rectStrike.top = spriteY;
			_strike.setTextureRect(rectStrike);

			if (frame >= 7) {	// assets strike hanya 7
				frame = 0;
				target = 10;
				strike = false;
			}
		}
	}
};