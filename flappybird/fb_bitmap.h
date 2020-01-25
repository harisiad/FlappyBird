#pragma once
#include "Globals.h"

class Window {
protected:
	int width;
	int height;

	bool fullscreen;
public:
	Window();

	void init(int,int,bool);
	void setWidth(int _width) { width = _width; }
	int getWidth(){ return width; }
	void setHeight(int _height) { height = _height; }
	int getHeight(){ return height; }

	bool getFullScreen(){ return fullscreen; }
};

class FbBackground {
protected:
	float x;
	float y;
	int bgwidth;
	int bgheight;
	float velX;
	float velY;

	ALLEGRO_BITMAP *bg;

	Window *win;
public:
	FbBackground();
	FbBackground(ALLEGRO_BITMAP*,int,int,Window*);

	void setX(int);
	float getX();
	void setvelX(float);
	float getvelX();

	void setY(float);
	float getY();
	void setvelY(float);
	float getvelY();

	void setBgWidth(int);
	int getBgWidth();
	void setBgHeight(int);
	int getBgHeight();

	void setImage(ALLEGRO_BITMAP*);
	ALLEGRO_BITMAP* getImage();

	void updateBackground();
	void drawBackground();
	
};

class GroundBk : public FbBackground {
private:
	int boundx;
	int boundy;

public:
	GroundBk();
	GroundBk(ALLEGRO_BITMAP*, int, int,Window*);

	void setBoundX(int);
	int getBoundX();
	void setBoundY(int);
	int getBoundY();

	void drawGround();
	bool groundCollision(int, int);
};

class PipeBk : public FbBackground {
private:
	int boundXup;
	int boundYup;
	int boundXdown;
	int boundYdown;

	int boundFreeX;
	int boundFreeY;

	bool alive;

public:
	PipeBk();
	PipeBk(ALLEGRO_BITMAP*, int, int,Window*);

	void setBoundXup(int);
	int getBoundXup();
	void setBoundYup(int);
	int getBoundYup();
	void setBoundXdown(int);
	int getBoundXdown();
	void setBoundYdown(int);
	int getBoundYdown();

	int getBoundFreeX() { return boundFreeX; }
	int getBoundFreeY() { return boundFreeY; }

	void setAlivePipe(bool value) { alive = value; }
	bool getAlivePipe(){ return alive; }

	bool groundCollision(int,int);
	void drawPipes();
	void updatePipes();
	void startPipes(FbBackground,int);
};