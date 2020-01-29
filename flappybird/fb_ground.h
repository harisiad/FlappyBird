#ifndef _FLAPPYBIRD_ENVIRONMENT_GROUND_H_
#define _FLAPPYBIRD_ENVIRONMENT_GROUND_H_

#include "fb_bitmap.h"

class GroundBk : public FbBackground
{
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

	void drawGround();
	bool groundCollision(int, int);
};

#endif