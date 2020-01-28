#pragma once

#include "fb_globals.h"
#include "fb_bitmap.h"

class Player {
private:
	int score;
	int highscore;
	bool gameOver;
	bool godMode;

protected:
	float x;
	float y;
	float velX;
	float velY;
	float gravity;
	float rotation;

	int boundX;
	int boundY;

	int maxframe;
	int currframe;
	int framecount;
	int framedelay;
	int framewidth;
	int frameheight;
	int animationColumns;
	int animationDirection;

	int animationRow;

	ALLEGRO_BITMAP *image;
public:

	Player(ALLEGRO_BITMAP* image = NULL);
	void Destroy();

	void updatePlayer();
	void gravityPull(int);
	void drawPlayer();

	void setX(float x) { Player::x = x; }
	float getX() { return x; }
	void setY(float){ Player::y = y; }
	float getY(){ return y; }

	void setBoundX(int boundX){ Player::boundX = boundX; }
	int getBoundX() { return boundX; }
	void setBoundY(int boundY){ Player::boundY = boundY; }
	int getBoundY(){ return boundY; }

	void addScore() { score++; }
	int getScore() { return score; }
	bool isGameOver() { return gameOver; }
	void setGameOver() { gameOver = true; }
	void setHighscore(int _highscore) { highscore = _highscore; }
	int getHighscore() { return highscore; }

	void setGodModeOn() { godMode = true; }
	void setGodModeOff() { godMode = false; }
	bool getGodMode() { return godMode; }

	void gainHeight();
	void resetAnimation();

	bool collidePipes(PipeBk*,GroundBk,Window*);
	bool collideGround(GroundBk);
	bool passMark(PipeBk*);

};