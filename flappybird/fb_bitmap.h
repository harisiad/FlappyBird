#ifndef _FLAPPYBIRD_ENVIRONMENT_BITMAP_H_
#define _FLAPPYBIRD_ENVIRONMENT_BITMAP_H_

#include "fb_globals.h"
#include "fb_window.h"

class FbBackground 
{
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

#endif