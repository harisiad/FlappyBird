#ifndef _FLAPPYBIRD_ENVIRONMENT_GROUND_H_
#define _FLAPPYBIRD_ENVIRONMENT_GROUND_H_

#include "fb_globals.h"
#include "fb_window.h"
#include "fb_game_object.h"

class GroundBk : public GameObject {
private:
	int boundx;
	int boundy;

public:
	GroundBk();
	GroundBk(ALLEGRO_BITMAP*, int, int, Window*);

	void setBoundX(int);
	int getBoundX();
	void setBoundY(int);
	int getBoundY();

	void update();
	void draw();

	void drawGround();
	bool groundCollision(int, int);
};

#endif