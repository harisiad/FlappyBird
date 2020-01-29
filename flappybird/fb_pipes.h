#ifndef _FLAPPYBIRD_ENVIRONMENT_PIPES_H_
#define _FLAPPYBIRD_ENVIRONMENT_PIPES_H_

#include "fb_bitmap.h"

class PipeBk : public FbBackground
{
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
	PipeBk(ALLEGRO_BITMAP*, int, int, Window*);

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
	bool getAlivePipe() { return alive; }

	bool groundCollision(int, int);
	void drawPipes();
	void updatePipes();
	void startPipes(FbBackground, int);
};

#endif
